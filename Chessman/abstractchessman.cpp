#include "abstractchessman.h"

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
