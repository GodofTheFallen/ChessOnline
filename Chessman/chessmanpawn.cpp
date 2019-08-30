#include "chessmanpawn.h"

ChessmanPawn::ChessmanPawn(const ChessColor &_color, const POS &_pos): AbstractChessman(ChessType::PAWN, _color, _pos)
{
    switch (color) {
    case ChessColor::BLACK:
        orirow = 7;
        forw = POS(0,-1);
        capt[0] = POS(-1,-1);
        capt[1] = POS(1,-1);
        break;
    case ChessColor::WHITE:
        orirow = 2;
        forw = POS(0,1);
        capt[0] = POS(-1,1);
        capt[1] = POS(1,1);
        break;
    }
}

QList<MoveInfo> ChessmanPawn::getMoves(AbstractChessman *board[]) const
{
    QList<MoveInfo> Q;
    POS cur = pos + forw;
    if (check(cur))
        if (!board[curve(cur)]) {
            if (cur.second == 1 || cur.second == 8) Q.append(MoveInfo(MoveType::PROMOTION,cur));
            else Q.append(MoveInfo(MoveType::MOVE,cur));
            if (pos.second == orirow && !board[curve(cur + forw)]) Q.append(MoveInfo(MoveType::MOVE,cur+forw));
        }
    for (int i = 0; i < 2; ++i) {
        cur = pos + capt[i];
        if (!check(cur)) continue;
        if (!board[curve(cur)]) continue;
        if (board[curve(cur)]->getColor() != getColor()) {
            if (cur.second == 1 || cur.second == 8) Q.append(MoveInfo(MoveType::PROMOTION,cur));
            else Q.append(MoveInfo(MoveType::CAPTURE,cur));
        }
    }
    return Q;
}

QPixmap ChessmanPawn::getPic()
{
    switch (getColor()) {
    case ChessColor::BLACK:
        return QPixmap(":/Chessman/pic/black_pawn.png");
    case ChessColor::WHITE:
        return QPixmap(":/Chessman/pic/white_pawn.png");
    }
}
