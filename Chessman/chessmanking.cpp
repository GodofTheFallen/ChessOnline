#include "chessmanking.h"

ChessmanKing::ChessmanKing(const ChessColor &_color, const POS &_pos):AbstractChessman (ChessType::KING, _color, _pos) {}

const POS ChessmanKing::mv[8] = {POS(0,1),POS(1,1),POS(1,0),POS(1,-1),POS(0,-1),POS(-1,-1),POS(-1,0),POS(-1,1)};

QList<MoveInfo> ChessmanKing::getMoves(AbstractChessman *board[]) const
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

QPixmap ChessmanKing::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_king.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_king.png");
    }
}
