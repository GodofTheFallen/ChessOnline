#ifndef CHESSCONNECTION_H
#define CHESSCONNECTION_H

#include <QObject>

class ChessConnection : public QObject
{
    Q_OBJECT
public:
    explicit ChessConnection(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CHESSCONNECTION_H
