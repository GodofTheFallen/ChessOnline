#include "startserver.h"
#include "ui_startserver.h"

StartServer::StartServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartServer)
{
    ui->setupUi(this);
}

StartServer::~StartServer()
{
    delete ui;
}
