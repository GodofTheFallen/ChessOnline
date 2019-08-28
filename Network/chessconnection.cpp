#include "chessconnection.h"

#include <QMessageBox>
#include <QTextCodec>

bool ChessConnection::isHost() const
{
    return Host;
}

void ChessConnection::setHost(bool value)
{
    Host = value;
    if (Server) delete Server;
    Server = nullptr;
    if (Socket) delete Socket;
    Socket = nullptr;
}

void ChessConnection::startHost()
{
    Waiting *Msg = new Waiting;
    Msg->setWindowTitle("");
    int timecnt=0;
    Msg->setText("等待连接……"+QString::number(timecnt));
    Msg->show();
    if (Ticker) delete Ticker;
    Ticker = new QTimer;
    connect(Msg,&QMessageBox::rejected,this,[this]{
        if (Ticker) delete Ticker;
        Ticker = nullptr;
        Server->close();
        delete Server;
        Server = nullptr;
        emit startHostFailed();
    });
    connect(Ticker,&QTimer::timeout,this,[Msg,&timecnt](){
        ++timecnt;Msg->setText("等待连接……"+QString::number(timecnt));
    });
    Ticker->start(1000);
    Server = new QTcpServer(this);
    Server->listen();
    connect(Server,&QTcpServer::newConnection,this,[this]{
        if (Socket) return;
        Socket = Server->nextPendingConnection();
        emit startHostSuccess();
        //connect(Socket,&QTcpSocket::close,)
    });
}

ChessConnection::ChessConnection(QObject *parent) : QObject(parent)
{
    Server = nullptr;
    Socket = nullptr;
    Ticker = nullptr;
}
