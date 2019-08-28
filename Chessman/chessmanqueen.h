#ifndef CHESSMANQUEEN_H
#define CHESSMANQUEEN_H

#include "abstractchessman.h"

class ChessmanQueen : public AbstractChessman
{
public:
    ChessmanQueen(const ChessColor &_color, const POS &_pos);
    QList<MoveInfo> getMoves(AbstractChessman *[]) const;
    static const POS mv[8];
    QPixmap getPic();
};

#endif // CHESSMANQUEEN_H
