#ifndef CHESSMANBISHOP_H
#define CHESSMANBISHOP_H

#include "abstractchessman.h"

class ChessmanBishop : public AbstractChessman
{
public:
    ChessmanBishop(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    static const POS mv[4];
    QPixmap getPic();
};

#endif // CHESSMANBISHOP_H
