#include "connectserver.h"
#include "ui_connectserver.h"

ConnectServer::ConnectServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectServer)
{
    ui->setupUi(this);
}

ConnectServer::~ConnectServer()
{
    delete ui;
}
