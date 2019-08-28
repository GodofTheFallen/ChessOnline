#include "chessinfo.h"

ChessType ChessInfo::getType() const
{
    return type;
}

ChessColor ChessInfo::getColor() const
{
    return color;
}

POS ChessInfo::getPos() const
{
    return pos;
}

ChessInfo::ChessInfo(const ChessType &_type, const ChessColor &_color, const POS &_pos): type(_type), color(_color), pos(_pos) {}
