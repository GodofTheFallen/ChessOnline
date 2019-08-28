#ifndef CHESSMANROOK_H
#define CHESSMANROOK_H

#include "abstractchessman.h"

class ChessmanRook : public AbstractChessman
{
public:
    ChessmanRook(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    static const POS mv[4];
    QPixmap getPic();
};

#endif // CHESSMANROOK_H
