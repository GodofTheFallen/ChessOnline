#ifndef CHESSCONNECTION_H
#define CHESSCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "chessmessage.h"

class ChessConnection: public QObject
{
    Q_OBJECT

private:
    bool Host;
    QTcpServer *Server;
    QTcpSocket *Socket;

signals:
    void connectionSuccess();

    void messsageReady(ChessMessage);

    void ruleReceived(int);

public:
    ChessConnection(bool _isHost);
    ~ChessConnection();

    bool isHost() const;

    int startHost();

    void disConnect();

    void startConnect(const QHostAddress &, quint16);

    bool sendMsg(const ChessMessage&);

    void getMsg();

    bool sendRules(int);
};

#endif // CHESSCONNECTION_H
