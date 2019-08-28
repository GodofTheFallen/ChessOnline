#include "chessboard.h"
#include <cmath>

ChessMessage ChessBoard::genMessage(MsgType _Type)
{
    return ChessMessage(ChessInfoList, _Type);
}

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    connect(&Timer,&QTimer::timeout,this,&ChessBoard::timeDec);
    for (int i = 0; i < 64; ++i) Board[i] = nullptr;
    initialize();
}

ChessBoard::~ChessBoard() {}

const QPoint ChessBoard::OPos(1,601);
const int ChessBoard::GridWidth = 75;
const double ChessBoard::XScale = ChessBoard::GridWidth;
const double ChessBoard::YScale = -ChessBoard::GridWidth;

const QColor ChessBoard::ColorCho = QColor(193, 95, 245, 64);
const QColor ChessBoard::ColorChoE = QColor(193, 95, 245, 255);

const QColor ChessBoard::ColorMv = QColor(0, 193, 255, 64);
const QColor ChessBoard::ColorMvE = QColor(0, 193, 255, 255);

const QColor ChessBoard::ColorCap = QColor(237, 45, 67, 64);
const QColor ChessBoard::ColorCapE = QColor(237, 45, 67, 255);

const QColor ChessBoard::ColorPro = QColor(243, 191, 16, 64);
const QColor ChessBoard::ColorProE = QColor(243, 191, 16, 255);

const QColor ChessBoard::ColorCas = QColor(0, 255, 0, 64);
const QColor ChessBoard::ColorCasE = QColor(0, 255, 0, 255);

AbstractChessman* CreateChessman(const ChessInfo &CI)
{
    switch (CI.getType()) {
    case ChessType::KING:
        return new ChessmanKing(CI.getColor(),CI.getPos());
    case ChessType::QUEEN:
        return new ChessmanQueen(CI.getColor(),CI.getPos());
    case ChessType::BISHOP:
        return new ChessmanBishop(CI.getColor(),CI.getPos());
    case ChessType::KNIGHT:
        return new ChessmanKnight(CI.getColor(),CI.getPos());
    case ChessType::ROOK:
        return new ChessmanRook(CI.getColor(),CI.getPos());
    case ChessType::PAWN:
        return new ChessmanPawn(CI.getColor(),CI.getPos());
    }
    return nullptr;
}

void ChessBoard::startOperating()
{
    Operating = true;
    remTime = TIME_MAX;
    emit timeDisplay(remTime);
    Timer.start(1000);
}

void ChessBoard::setTIME_MAX(int value)
{
    TIME_MAX = value;
}

void ChessBoard::loadFromMsg()
{
    for (int i = 0; i < 64; ++i) if (Board[i]) {delete Board[i]; Board[i] = nullptr;}
    for (auto CI : ChessInfoList)
        Board[curve(CI.getPos())] = CreateChessman(CI);
}

void ChessBoard::saveToMsg()
{
    ChessInfoList.clear();
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            if (Board[curve(i,j)]) ChessInfoList.append(toChessInfo(Board[curve(i,j)]));
}

void ChessBoard::timeDec()
{
    --remTime;
    emit timeDisplay(remTime);
    if (!remTime) {
        Timer.stop();
        timeUseUp();
    }
}

void ChessBoard::stopOperating()
{
    Timer.stop();
    Operating = false;
}

void ChessBoard::timeUseUp()
{
    emit sendMsg(genMessage(MsgType::Timeout));
    stopOperating();
}

void ChessBoard::initialize()
{
    ChessInfoList.clear();
    ChessInfoList.append(ChessInfo(ChessType::ROOK,ChessColor::WHITE,POS(1,1)));
    ChessInfoList.append(ChessInfo(ChessType::KNIGHT,ChessColor::WHITE,POS(2,1)));
    ChessInfoList.append(ChessInfo(ChessType::BISHOP,ChessColor::WHITE,POS(3,1)));
    ChessInfoList.append(ChessInfo(ChessType::QUEEN,ChessColor::WHITE,POS(4,1)));
    ChessInfoList.append(ChessInfo(ChessType::KING,ChessColor::WHITE,POS(5,1)));
    ChessInfoList.append(ChessInfo(ChessType::BISHOP,ChessColor::WHITE,POS(6,1)));
    ChessInfoList.append(ChessInfo(ChessType::KNIGHT,ChessColor::WHITE,POS(7,1)));
    ChessInfoList.append(ChessInfo(ChessType::ROOK,ChessColor::WHITE,POS(8,1)));
    ChessInfoList.append(ChessInfo(ChessType::ROOK,ChessColor::BLACK,POS(1,8)));
    ChessInfoList.append(ChessInfo(ChessType::KNIGHT,ChessColor::BLACK,POS(2,8)));
    ChessInfoList.append(ChessInfo(ChessType::BISHOP,ChessColor::BLACK,POS(3,8)));
    ChessInfoList.append(ChessInfo(ChessType::KING,ChessColor::BLACK,POS(4,8)));
    ChessInfoList.append(ChessInfo(ChessType::QUEEN,ChessColor::BLACK,POS(5,8)));
    ChessInfoList.append(ChessInfo(ChessType::BISHOP,ChessColor::BLACK,POS(6,8)));
    ChessInfoList.append(ChessInfo(ChessType::KNIGHT,ChessColor::BLACK,POS(7,8)));
    ChessInfoList.append(ChessInfo(ChessType::ROOK,ChessColor::BLACK,POS(8,8)));
    for (int i = 1; i <= 8; ++i) {
        ChessInfoList.append(ChessInfo(ChessType::PAWN,ChessColor::WHITE,POS(i,2)));
        ChessInfoList.append(ChessInfo(ChessType::PAWN,ChessColor::BLACK,POS(i,7)));
    }
    loadFromMsg();
    TIME_MAX = 30;
    Player = ChessColor::WHITE;
    ChosenChessman = nullptr;
}

void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter Painter(this);

    Painter.translate(OPos);
    QFont font = Painter.font();
    font.setPixelSize(12);
    font.setBold(true);
    font.setFamily("Arial");
    Painter.setFont(font);
    auto ScaledPoint = [=](double x,double y) {return QPointF(x*XScale,y*YScale);};
    auto Cell = [=](int x,int y,double d = 0.04) {return QRectF(ScaledPoint(x-1+d,y-d),ScaledPoint(x-d,y-1+d));};
    auto PaintCell = [&](int x,int y,double d = 0.04){
        Painter.drawRect(Cell(x,y,d));
    };


    //Paint chessboard
    Painter.setBrush(Qt::lightGray);
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            if ((i + j) % 2 == 0) PaintCell(i,j,0);
    Painter.setBrush(Qt::white);
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            if ((i + j) % 2 == 1) PaintCell(i,j,0);

    //Paint labels
    Painter.setPen(Qt::black);
    for (int i = 1; i <= 8; ++i) {
        Painter.drawText(Cell(i,1),QString('A'+i-1),Qt::AlignRight|Qt::AlignBottom);
        Painter.drawText(Cell(1,i),QString::number(i),Qt::AlignLeft|Qt::AlignTop);
    }


    //Paint chessmen
    Painter.setPen(Qt::NoPen);
    Painter.setBrush(Qt::NoBrush);
    Painter.setRenderHint(QPainter::SmoothPixmapTransform);
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            if (Board[curve(i,j)])
                Painter.drawPixmap(Cell(i,j).toRect(),Board[curve(i,j)]->getPic());

    //Paint moves
    if (ChosenChessman) {
        Painter.setPen(ColorChoE);
        Painter.setBrush(ColorCho);
        PaintCell(ChosenChessman->getPos().first,ChosenChessman->getPos().second);
        for (auto mv : MoveList) {
            switch (mv.first) {
            case MoveType::MOVE:
                Painter.setPen(ColorMvE);
                Painter.setBrush(ColorMv);
                break;
            case MoveType::CAPTURE:
                Painter.setPen(ColorCapE);
                Painter.setBrush(ColorCap);
                break;
            case MoveType::PROMOTION:
                Painter.setPen(ColorProE);
                Painter.setBrush(ColorPro);
                break;
            case MoveType::CASTLING:
                Painter.setPen(ColorCasE);
                Painter.setBrush(ColorCas);
                break;
            }
            PaintCell(mv.second.first,mv.second.second);
        }
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (!Operating) return;
    int x = int(floor((event->x()-OPos.x())/XScale));
    int y = int(floor((event->y()-OPos.y())/YScale));
    if (!check(x,y)) return;
    if (event->button() == Qt::LeftButton) {
        if (!ChosenChessman) {
            if (!Board[curve(x,y)]) return;
            if (Board[curve(x,y)]->getColor() != Player) return;
            ChosenChessman = Board[curve(x,y)];
            MoveList = ChosenChessman->getMoves(Board);
        }
    }
    else {
        ChosenChessman = nullptr;
        MoveList.clear();
    }
}
