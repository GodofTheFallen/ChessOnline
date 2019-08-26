#ifndef ABSTRACTCHESSMAN_H
#define ABSTRACTCHESSMAN_H

#include <QObject>

typedef enum{KING,QUEEN,BISHOP,KNIGHT,ROOK,PAWN} ChessType;

typedef QPair<int,int> POS;

class AbstractChessman : public QObject
{
    Q_OBJECT
public:
    explicit AbstractChessman(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ABSTRACTCHESSMAN_H
