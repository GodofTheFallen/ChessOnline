#ifndef CHESSMANKNIGHT_H
#define CHESSMANKNIGHT_H

#include "abstractchessman.h"

class ChessmanKnight : public AbstractChessman
{
public:
    ChessmanKnight(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    const static POS mv[8];
    QPixmap getPic();
};

#endif // CHESSMANKNIGHT_H
