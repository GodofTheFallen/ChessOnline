#include "chessconnection.h"

ChessConnection::ChessConnection(bool _isHost): Host(_isHost)
{
    Server = nullptr;
    Socket = nullptr;
}

ChessConnection::~ChessConnection()
{
    disConnect();
}

bool ChessConnection::isHost() const
{
    return Host;
}

int ChessConnection::startHost()
{
    if (Server) return 0;
    Server = new QTcpServer;
    if (!Server->listen()) return 0;
    connect(Server,&QTcpServer::newConnection,[this]{
        Socket = Server->nextPendingConnection();
        connect(Socket,&QTcpSocket::readyRead,this,&ChessConnection::getMsg);
        emit connectionSuccess();
    });
    return Server->serverPort();
}

void ChessConnection::disConnect()
{
    if (Server) {Server->close(); delete Server;}
    if (Socket) {Socket->close(); delete Socket;}
}

void ChessConnection::startConnect(const QHostAddress & _hostAdd, quint16 _port)
{
    if (isHost()) return;
    if (Socket) return;
    Socket = new QTcpSocket;
    connect(Socket,&QTcpSocket::connected,this,&ChessConnection::connectionSuccess);
    Socket->connectToHost(_hostAdd,_port);
    connect(Socket,&QTcpSocket::readyRead,this,&ChessConnection::getMsg);
}

bool ChessConnection::sendMsg(const ChessMessage &Msg)
{
    Socket->write(Msg.transToJson().toJson());
    return Socket->waitForBytesWritten();
}

void ChessConnection::getMsg()
{
    QJsonDocument JD = QJsonDocument::fromJson(Socket->readAll());
    qDebug() << JD;
    if (JD.array().at(0).isString()) emit ruleReceived(JD.array().at(1).toInt());
    else emit messsageReady(ChessMessage(JD));
}

bool ChessConnection::sendRules(int time)
{
    QJsonArray JA;
    JA.append("Time");
    JA.append(time);
    QJsonDocument JD;
    JD.setArray(JA);
    Socket->write(JD.toJson());
    return Socket->waitForBytesWritten();
}
