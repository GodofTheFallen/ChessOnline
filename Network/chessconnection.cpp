#include "chessconnection.h"

#include <QEventLoop>

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
    if (!isHost()) return 0;
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
    QByteArray QBA;
    QDataStream QDS(&QBA,QIODevice::WriteOnly);
    QDS.setVersion(QDataStream::Qt_5_13);
    QDS << Msg.transToJson().toJson();
    Socket->write(QBA);
    //Socket->flush();
    qDebug() << "send " << Msg.transToJson();
    return Socket->waitForBytesWritten();
}

void ChessConnection::getMsg()
{
    QByteArray QBA = Socket->readAll();
    QDataStream QDS(&QBA,QIODevice::ReadOnly);
    QDS.setVersion(QDataStream::Qt_5_13);
    QByteArray Sect;
    do {
        QDS >> Sect;
        if (Sect.isEmpty()) return;
        QJsonDocument JD;
        QJsonParseError ERR;
        JD = QJsonDocument::fromJson(Sect,&ERR);
        qDebug() << "receive " << JD;
        if (JD.isNull()) {
            qDebug() << ERR.errorString();
            throw ERR.errorString();
        }
        if (JD.array().at(0).isString()) emit ruleReceived(JD.array().at(1).toInt());
        else emit messsageReady(ChessMessage(JD));
    }while (1);
}

bool ChessConnection::sendRules(int time)
{
    QJsonArray JA;
    JA.append("Time");
    JA.append(time);
    QJsonDocument JD;
    JD.setArray(JA);
    QByteArray QBA;
    QDataStream QDS(&QBA,QIODevice::WriteOnly);
    QDS.setVersion(QDataStream::Qt_5_13);
    QDS << JD.toJson();
    Socket->write(QBA);
    return true;
}
