#ifndef CHESSMANKING_H
#define CHESSMANKING_H

#include "abstractchessman.h"

class ChessmanKing : public AbstractChessman
{
public:
    ChessmanKing(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    static const POS mv[8];
    QPixmap getPic();
};

#endif // CHESSMANKING_H
