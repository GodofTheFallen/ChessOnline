#ifndef CHESSCONNECTION_H
#define CHESSCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "waiting.h"

class ChessConnection : public QObject
{
    Q_OBJECT

private:
    bool Host;
    QTcpServer *Server;
    QTcpSocket *Socket;

    QTimer *Ticker;

public:
    explicit ChessConnection(QObject *parent = nullptr);

    bool isHost() const;

signals:
    void startHostFailed();

    void startHostSuccess();

public slots:
    void setHost(bool value);

    void startHost();

};

#endif // CHESSCONNECTION_H
