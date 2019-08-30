#include "startserver.h"
#include "ui_startserver.h"

StartServer::StartServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartServer)
{
    ui->setupUi(this);
    status = false;
    newConnection = nullptr;
}

StartServer::~StartServer()
{
    delete ui;
}

void StartServer::on_pushButton_clicked()
{
    if (!status) {
        status = true;
        ui->pushButton->setText("取消建立");
        newConnection = new ChessConnection(true);
        int port = newConnection->startHost();
        ui->lineEdit->setText(QString::number(port));
        Timer = new QTimer(this);
        remTime = 0;
        ui->label_msg->setText("等待连接..."+QString::number(remTime));
        connect(Timer,&QTimer::timeout,[this]{
            remTime = remTime + 1;
            ui->label_msg->setText("等待连接..."+QString::number(remTime));
        });
        connect(newConnection,&ChessConnection::connectionSuccess,[this]{
            Timer->stop();
            delete Timer;
            Timer = nullptr;
            emit genConnection(newConnection);
            close();
        });
        Timer->start(1000);
    }
    else {
        cancel();
        ui->label_msg->clear();
    }

}

void StartServer::cancel()
{
    if (!status) return;
    status = false;
    ui->pushButton->setText("开始连接");
    if (Timer) delete Timer;
    Timer = nullptr;
    if (newConnection) delete newConnection;
    newConnection = nullptr;
}
