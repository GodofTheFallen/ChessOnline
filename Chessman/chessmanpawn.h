#ifndef CHESSMANPAWN_H
#define CHESSMANPAWN_H

#include "abstractchessman.h"

class ChessmanPawn : public AbstractChessman
{
public:
    ChessmanPawn(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    POS forw,capt[2];
    int orirow;
    QPixmap getPic();
};

#endif // CHESSMANPAWN_H
