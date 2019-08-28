#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    CB(this),
    network(this)
{
    serverUi = nullptr;
    connectUi = nullptr;
    ui->setupUi(this);
    ui->label_check->hide();
    setFixedSize(680,642);
    CB.setGeometry(10,32,602,602);
    CB.layout();
    connect(&CB, &ChessBoard::timeDisplay, [this](int num){ui->lcdNumber_Timer->display(num);});
    CB.startOperating();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_host_triggered()
{
    if (serverUi) delete serverUi;
    serverUi = new StartServer(this);
    connect(serverUi,&StartServer::accepted,this,&MainWindow::onServeruiAccept);
    serverUi->exec();
}

void MainWindow::on_action_connect_triggered()
{
    if (connectUi) delete connectUi;
    connectUi = new ConnectServer(this);
    connect(connectUi,&ConnectServer::accepted,this,&MainWindow::onConnectuiAccept);
    connectUi->exec();
}

void MainWindow::onServeruiAccept()
{
    network.setHost(true);
    network.startHost();

}

void MainWindow::onConnectuiAccept()
{

}


