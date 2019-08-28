#include "chessmanqueen.h"

ChessmanQueen::ChessmanQueen(const ChessColor &_color, const POS &_pos): AbstractChessman(ChessType::QUEEN, _color ,_pos) {}

const POS ChessmanQueen::mv[8] = {POS(0,1),POS(1,1),POS(1,0),POS(1,-1),POS(0,-1),POS(-1,-1),POS(-1,0),POS(-1,1)};

QList<MoveInfo> ChessmanQueen::getMoves(AbstractChessman *board[]) const
{
    QList<MoveInfo> Q;
    for (int i = 0; i < 8; ++i) {
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

QPixmap ChessmanQueen::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_queen.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_queen.png");
    }
}
