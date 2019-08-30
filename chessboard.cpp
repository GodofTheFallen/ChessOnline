#include "chessboard.h"
#include "Chessman/pawnpromotion.h"
#include "ui_pawnpromotion.h"
#include <QTextStream>
#include <cmath>

QList<ChessInfo> ChessBoard::getChessInfoList() const
{
    return ChessInfoList;
}

QString ChessBoard::getRemBoard()
{
    QString RemS;
    QTextStream REM(&RemS,QIODevice::WriteOnly);
    QMap<ChessType,QList<POS>> WMap,BMap;
    for (auto CI : ChessInfoList) {
        switch (CI.getColor()) {
        case ChessColor::WHITE:
            WMap[CI.getType()].append(CI.getPos()); break;
        case ChessColor::BLACK:
            BMap[CI.getType()].append(CI.getPos()); break;
        }
    }
    auto writeName = [&](ChessType K) {
        switch (K) {
        case ChessType::KING:
            REM << "king "; break;
        case ChessType::PAWN:
            REM << "pawn "; break;
        case ChessType::ROOK:
            REM << "rook "; break;
        case ChessType::QUEEN:
            REM << "queen "; break;
        case ChessType::BISHOP:
            REM << "bishop "; break;
        case ChessType::KNIGHT:
            REM << "knight "; break;
        }
    };
    auto writeWhite = [&]{
        REM << "white" << endl;
        for (auto KY : WMap.uniqueKeys()) {
            if (WMap[KY].empty()) continue;
            writeName(KY);
            REM << WMap[KY].size();
            for (auto P : WMap[KY])
                REM << " " << QChar(P.first + 'a' -1) << P.second;
            REM << endl;
        }
    };
    auto writeBlack = [&]{
        REM << "black" << endl;
        for (auto KY : BMap.uniqueKeys()) {
            if (BMap[KY].empty()) continue;
            writeName(KY);
            REM << BMap[KY].size();
            for (auto P : BMap[KY])
                REM << " " << QChar(P.first + 'a' -1) << P.second;
            REM << endl;
        }
    };
    if ((Player == ChessColor::WHITE && Operating) || (Player == ChessColor::BLACK && !Operating)) {
        writeWhite();
        writeBlack();
    }
    else {
        writeBlack();
        writeWhite();
    }
    return RemS;
}

int ChessBoard::getTIME_MAX() const
{
    return TIME_MAX;
}

ChessMessage ChessBoard::genMessage(MsgType _Type)
{
    saveToMsg();
    return ChessMessage(ChessInfoList, _Type);
}

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    connect(&Timer,&QTimer::timeout,this,&ChessBoard::timeDec);
    for (int i = 0; i < 64; ++i) Board[i] = nullptr;
    TIME_MAX = 30;
    Operating = false;
    remTime = 0;
    Player = ChessColor::WHITE;
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

void ChessBoard::stopOperating()
{
    Timer.stop();
    Operating = false;
}

void ChessBoard::setTIME_MAX(int value)
{
    TIME_MAX = value;
}

void ChessBoard::loadFromMsg() //rebuild
{
    for (int i = 0; i < 64; ++i) if (Board[i]) {delete Board[i]; Board[i] = nullptr;}
    POS King;
    for (auto CI : ChessInfoList) {
        Board[curve(CI.getPos())] = CreateChessman(CI);
        if (CI.getType() == ChessType::KING && CI.getColor() == Player) King = CI.getPos();
    }
    repaint();
    bool *atk = getAtkRange(Board,Player);
    bool Check = atk[curve(King)];
    bool NoMove = true;
    emit inCheck(atk[curve(King)]);
    for (int i = 0; i < 64; ++i) if (Board[i]) if (Board[i]->getColor() == Player) {
                if (!NoMove) break;
                QList<MoveInfo> curMVList = Board[i]->getMoves(Board);
                for (auto mv : curMVList) {
                    if (checkMoveValidity(mv,Board[i]->getPos(),Board)) {
                        NoMove = false;
                        break;
                    }
                }
            }
    if (NoMove) {
        if (Check) emit sendMsg(genMessage(MsgType::Win));
        else emit sendMsg(genMessage(MsgType::Draw));
    }
}

void ChessBoard::saveToMsg()
{
    ChessInfoList.clear();
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
            if (Board[curve(i,j)]) ChessInfoList.append(toChessInfo(Board[curve(i,j)]));
    emit inCheck(false);
}

void ChessBoard::receiveMsg(ChessMessage Msg)
{
    ChessInfoList = Msg.getChessmenInfo();
    loadFromMsg();
    repaint();
    if (Msg.getType() == MsgType::Move) startOperating();
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
    ChessInfoList.append(ChessInfo(ChessType::QUEEN,ChessColor::BLACK,POS(4,8)));
    ChessInfoList.append(ChessInfo(ChessType::KING,ChessColor::BLACK,POS(5,8)));
    ChessInfoList.append(ChessInfo(ChessType::BISHOP,ChessColor::BLACK,POS(6,8)));
    ChessInfoList.append(ChessInfo(ChessType::KNIGHT,ChessColor::BLACK,POS(7,8)));
    ChessInfoList.append(ChessInfo(ChessType::ROOK,ChessColor::BLACK,POS(8,8)));
    for (int i = 1; i <= 8; ++i) {
        ChessInfoList.append(ChessInfo(ChessType::PAWN,ChessColor::WHITE,POS(i,2)));
        ChessInfoList.append(ChessInfo(ChessType::PAWN,ChessColor::BLACK,POS(i,7)));
    }
    loadFromMsg();
    ChosenChessman = nullptr;
    repaint();
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

void ChessBoard::timeUseUp()
{
    emit sendMsg(ChessMessage(ChessInfoList,MsgType::Timeout));
    stopOperating();
}

void ChessBoard::handleMove(MoveInfo mv)
{
    switch (mv.first) {
    case MoveType::MOVE:
        Board[curve(ChosenChessman->getPos())] = nullptr;
        ChosenChessman->setPos(mv.second);
        Board[curve(mv.second)] = ChosenChessman;
        break;
    case MoveType::CAPTURE:
        delete Board[curve(mv.second)];
        Board[curve(ChosenChessman->getPos())] = nullptr;
        ChosenChessman->setPos(mv.second);
        Board[curve(mv.second)] = ChosenChessman;
        break;
    case MoveType::PROMOTION:
    {
        AbstractChessman *NewChessman;
        PawnPromotion *PP = new PawnPromotion(this);
        //connect(PP,&PawnPromotion::rejected,[&]{PP->exec();});
        connect(PP,&PawnPromotion::accepted,[this,PP,mv,&NewChessman]{
            switch (PP->ui->comboBox->currentIndex()) {
            case 0: NewChessman = new ChessmanQueen(Player,mv.second); break;
            case 1: NewChessman = new ChessmanBishop(Player,mv.second); break;
            case 2: NewChessman = new ChessmanKnight(Player,mv.second); break;
            case 3: NewChessman = new ChessmanRook(Player,mv.second); break;
            } ;
        });
        PP->exec();
        PP->deleteLater();
        if (Board[curve(mv.second)]) delete Board[curve(mv.second)];
        Board[curve(ChosenChessman->getPos())] = nullptr;
        delete ChosenChessman;
        ChosenChessman = NewChessman;
        Board[curve(mv.second)] = ChosenChessman;
    }
        break;
    case MoveType::CASTLING:
        switch(mv.second.first) {
        case 3:
            Board[curve(ChosenChessman->getPos())] = nullptr;
            ChosenChessman->setPos(mv.second);
            Board[curve(mv.second)] = ChosenChessman;
            Board[curve(1,mv.second.second)]->setPos(mv.second+POS(1,0));
            Board[curve(mv.second+POS(1,0))] = Board[curve(1,mv.second.second)];
            Board[curve(1,mv.second.second)] = nullptr;
            break;
        case 7:
            Board[curve(ChosenChessman->getPos())] = nullptr;
            ChosenChessman->setPos(mv.second);
            Board[curve(mv.second)] = ChosenChessman;
            Board[curve(8,mv.second.second)]->setPos(mv.second+POS(-1,0));
            Board[curve(mv.second+POS(-1,0))] = Board[curve(8,mv.second.second)];
            Board[curve(8,mv.second.second)] = nullptr;
            break;
        }
        break;
    }
    ChosenChessman = nullptr;
    MoveList.clear();
    emit sendMsg(genMessage(MsgType::Move));
    stopOperating();
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
    int x = int(floor((event->x()-OPos.x())/XScale)+1);
    int y = int(floor((event->y()-OPos.y())/YScale)+1);
    if (!check(x,y)) return;
    if (event->button() == Qt::LeftButton) {
        if (!ChosenChessman) {
            if (!Board[curve(x,y)]) return;
            if (Board[curve(x,y)]->getColor() != Player) return;
            ChosenChessman = Board[curve(x,y)];
            QList<MoveInfo> curMVList = ChosenChessman->getMoves(Board);
            MoveList.clear();
            for (auto mv : curMVList) {
                if (checkMoveValidity(mv,ChosenChessman->getPos(),Board))
                    MoveList.append(mv);
            }
            repaint();
        }
        else {
            for (auto mv : MoveList) {
                if (mv.second==POS(x,y)) {
                    handleMove(mv);
                    repaint();
                    return;
                }
            }
        }
    }
    else {
        ChosenChessman = nullptr;
        MoveList.clear();
        repaint();
    }
}
