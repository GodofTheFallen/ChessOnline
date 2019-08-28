#include "chessmanrook.h"

ChessmanRook::ChessmanRook(const ChessColor &_color, const POS &_pos): AbstractChessman(ChessType::ROOK, _color, _pos) {}

const POS ChessmanRook::mv[4] = {POS(0,1),POS(0,-1),POS(-1,0),POS(1,0)};

QList<MoveInfo> ChessmanRook::getMoves(AbstractChessman *board[]) const
{
    QList<MoveInfo> Q;
    for (int i = 0; i < 4; ++i) {
        for (POS cur = pos + mv[i]; check(cur); cur += mv[i]) {
            if (!board[curve(cur)]) Q.append(MoveInfo(MoveType::MOVE,cur));
            else {
                if (board[curve(cur)]->getColor() != getColor()) Q.append(MoveInfo(MoveType::CAPTURE,cur));
                break;
            }
        }
    }
    return Q;
}

QPixmap ChessmanRook::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_rook.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_rook.png");
    }
}
