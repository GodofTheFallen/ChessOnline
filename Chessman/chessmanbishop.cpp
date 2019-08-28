#include "chessmanbishop.h"

ChessmanBishop::ChessmanBishop(const ChessColor &_color, const POS &_pos):AbstractChessman(ChessType::BISHOP, _color, _pos) {}

const POS ChessmanBishop::mv[4] = {POS(1,1),POS(1,-1),POS(-1,1),POS(-1,-1)};

QList<MoveInfo> ChessmanBishop::getMoves(AbstractChessman *board[]) const
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

QPixmap ChessmanBishop::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_bishop.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_bishop.png");
    }
}


