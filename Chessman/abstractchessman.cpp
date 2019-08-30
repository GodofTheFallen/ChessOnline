#include "abstractchessman.h"
#include "chessmen"

ChessType AbstractChessman::getType() const
{
    return type;
}

POS AbstractChessman::getPos() const
{
    return pos;
}

void AbstractChessman::setPos(const POS &value)
{
    pos = value;
}

ChessColor AbstractChessman::getColor() const
{
    return color;
}

AbstractChessman::AbstractChessman(const ChessType &_type, const ChessColor &_color, const POS &_pos):
    type(_type),
    color(_color),
    pos(_pos)
{}

AbstractChessman::~AbstractChessman()
{}


ChessInfo toChessInfo(AbstractChessman *chessman)
{
    return ChessInfo(chessman->getType(),chessman->getColor(),chessman->getPos());
}

int curve(int x, int y)
{
    return ((x-1)*8+y-1);
}

int curve(POS P)
{
    return curve(P.first,P.second);
}

int check(int x, int y)
{
    return (1 <= x && x <= 8 && 1 <= y && y <= 8);
}

bool check(POS P)
{
    return check(P.first,P.second);
}

POS operator + (const POS &P1,const POS &P2)
{
    return POS(P1.first+P2.first,P1.second+P2.second);
}

POS operator +=(POS &P1, const POS &P2)
{
    return P1=P1+P2;
}

bool *getAtkRange(AbstractChessman *board[], ChessColor alley)
{
    bool *atkRange = new bool[64];
    for (int i = 0; i < 64; ++i) atkRange[i] = false;
    QList<MoveInfo> curMv;
    for (int i = 0; i < 64; ++i) {
        if (!board[i]) continue;
        if (board[i]->getColor() == alley) continue;
        curMv = board[i]->getMoves(board);
        for (auto Mv : curMv)
            if (Mv.first == MoveType::CAPTURE) atkRange[curve(Mv.second)] = true;
    }
    return atkRange;
}

AbstractChessman* copyChess(AbstractChessman* oldChess)
{
    switch (oldChess->getType()) {
    case ChessType::KING: return new ChessmanKing(oldChess->getColor(),oldChess->getPos());
    case ChessType::PAWN: return new ChessmanPawn(oldChess->getColor(),oldChess->getPos());
    case ChessType::ROOK: return new ChessmanRook(oldChess->getColor(),oldChess->getPos());
    case ChessType::QUEEN: return new ChessmanQueen(oldChess->getColor(),oldChess->getPos());
    case ChessType::BISHOP: return new ChessmanBishop(oldChess->getColor(),oldChess->getPos());
    case ChessType::KNIGHT: return new ChessmanKnight(oldChess->getColor(),oldChess->getPos());
    }
}

bool checkMoveValidity(MoveInfo mv, POS ChosenPos, AbstractChessman *board[])
{
    AbstractChessman *Board[64];
    bool OK = true;
    for (int i = 0; i < 64; ++i)
        if (board[i]) Board[i] = copyChess(board[i]);
        else Board[i] = nullptr;
    AbstractChessman *ChosenChessman = Board[curve(ChosenPos)];
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
        if (Board[curve(mv.second)]) delete Board[curve(mv.second)];
        Board[curve(ChosenChessman->getPos())] = nullptr;
        ChosenChessman->setPos(mv.second);
        Board[curve(mv.second)] = ChosenChessman;
        break;
    case MoveType::CASTLING:
        Board[curve((mv.second.first+ChosenPos.first)/2,mv.second.second)] =
            new ChessmanKing(ChosenChessman->getColor(),POS((mv.second.first+ChosenPos.first)/2,mv.second.second));
        Board[curve(mv.second)] = new ChessmanKing(ChosenChessman->getColor(),mv.second);
        break;
    }
    bool *atkRange = getAtkRange(Board,ChosenChessman->getColor());
    for (int i = 0; i < 64; ++i) {
        if (atkRange[i] && Board[i] && Board[i]->getType()==ChessType::KING && Board[i]->getColor()==ChosenChessman->getColor()) {
            OK = false;
            break;
        }
    }
    for (int i = 0; i < 64; ++i)
        if (Board[i]) delete Board[i];
    delete [] atkRange;
    return OK;
}
