#include "chessmanknight.h"

ChessmanKnight::ChessmanKnight(const ChessColor &_color, const POS &_pos): AbstractChessman(ChessType::KNIGHT, _color, _pos) {}

const POS ChessmanKnight::mv[8] = {POS(1,2),POS(1,-2),POS(-1,-2),POS(-1,2),POS(2,1),POS(2,-1),POS(-2,-1),POS(-2,1)};

QList<MoveInfo> ChessmanKnight::getMoves(AbstractChessman *board[]) const
{
    QList<MoveInfo> Q;
    for (int i = 0; i < 8; ++i) {
        POS cur = pos + mv[i];
        if (!check(cur)) continue;
        if (!board[curve(cur)]) Q.append(MoveInfo(MoveType::MOVE,cur));
        else if (board[curve(cur)]->getColor() != getColor()) Q.append(MoveInfo(MoveType::CAPTURE,cur));
    }
    return Q;
}

QPixmap ChessmanKnight::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_knight.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_knight.png");
    }
}
