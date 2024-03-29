#ifndef ABSTRACTCHESSMAN_H
#define ABSTRACTCHESSMAN_H

#include <QPixmap>
#include "chessinfo.h"

class AbstractChessman //rebuild + CheckVal + getAtkRange
{
protected:
    ChessType type;
    ChessColor color;
    POS pos;

public:
    explicit AbstractChessman(const ChessType &_type, const ChessColor &_color, const POS &_pos);
    virtual ~AbstractChessman();
    ChessType getType() const;

    ChessColor getColor() const;

    POS getPos() const;
    void setPos(const POS &value);

    virtual QList<MoveInfo> getMoves(AbstractChessman *[]) const = 0;

    virtual QPixmap getPic() = 0;

};

ChessInfo toChessInfo(AbstractChessman*);

int curve(int,int);

int curve(POS);

int check(int,int);

bool check(POS);

POS operator + (const POS &P1,const POS &P2);

POS operator += (POS &P1,const POS &P2);

bool* getAtkRange(AbstractChessman*[],ChessColor);

bool checkMoveValidity(MoveInfo,POS,AbstractChessman*[]);

#endif // ABSTRACTCHESSMAN_H
