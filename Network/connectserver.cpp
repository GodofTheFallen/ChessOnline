#include "connectserver.h"
#include "ui_connectserver.h"

ConnectServer::ConnectServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectServer)
{
    ui->setupUi(this);
    status = false;
    newConnection = nullptr;
}

ConnectServer::~ConnectServer()
{
    delete ui;
}

void ConnectServer::on_pushButton_clicked()
{
    if (!status) {
        QHostAddress hostAddr;
        if (!hostAddr.setAddress(ui->lineEdit_serverIP->text())) {
            ui->label_msg->setText("IP地址不合法！");
            return;
        }
        bool ok;
        quint16 port = ui->lineEdit_port->text().toUShort(&ok);
        if (!ok) {
            ui->label_msg->setText("端口号不合法！");
            return;
        }
        status = true;
        ui->pushButton->setText("取消连接");
        newConnection = new ChessConnection(false);
        Timer = new QTimer(this);
        remTime = timeout;
        ui->label_msg->setText("正在连接..."+QString::number(remTime));
        connect(Timer,&QTimer::timeout,[this]{
            remTime = remTime - 1;
            ui->label_msg->setText("正在连接..."+QString::number(remTime));
            if (!remTime) {
                cancel();
                ui->label_msg->setText("连接失败");
            }
        });
        connect(newConnection,&ChessConnection::connectionSuccess,[this]{
            Timer->stop();
            delete Timer;
            Timer = nullptr;
            emit genConnection(newConnection);
            close();
        });
        Timer->start(1000);
        newConnection->startConnect(hostAddr,port);
    }
    else {
        cancel();
        ui->label_msg->clear();
    }
}

void ConnectServer::cancel()
{
    if (!status) return;
    status = false;
    ui->pushButton->setText("开始连接");
    if (Timer) delete Timer;
    Timer = nullptr;
    if (newConnection) delete newConnection;
    newConnection = nullptr;
}
