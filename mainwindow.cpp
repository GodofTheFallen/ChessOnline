#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_check->hide();
    ui->action_save->setEnabled(false);
    setFixedSize(680,642);

    network = nullptr;

    CB = new ChessBoard(this);

    CB->setGeometry(10,32,602,602);
    CB->layout();
    connect(CB, &ChessBoard::timeDisplay, [this](int num){ui->lcdNumber_Timer->display(num);});
    connect(CB, &ChessBoard::sendMsg,this,&MainWindow::sendMsg);

    ErrMsg = new QErrorMessage(this);
    ErrMsg->setWindowTitle("Error");
    ErrMsg->setWindowIcon(QIcon(":/warning.ico"));

    firstPlayer = ChessColor::WHITE;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_host_triggered()
{
    StartServer *startUi = new StartServer(this);
    connect(startUi,&StartServer::genConnection,this,&MainWindow::gameStart);
    startUi->exec();
    startUi->deleteLater();
}

void MainWindow::on_action_connect_triggered()
{
    ConnectServer *connectUi = new ConnectServer(this);
    connect(connectUi,&ConnectServer::genConnection,this,&MainWindow::gameStart);
    connectUi->exec();
    connectUi->deleteLater();
}

void MainWindow::on_action_setting_triggered()
{
    GameSetting *gameSetting = new GameSetting(this);
    connect(gameSetting,&GameSetting::settingTime,[this](int time){CB->setTIME_MAX(time);});
    gameSetting->exec();
    gameSetting->deleteLater();
}


void MainWindow::on_action_loaddefault_triggered()
{
    CB->initialize();
}

void MainWindow::on_action_load_triggered()
{
    QFile rem(QFileDialog::getOpenFileName());
    try {
#define ERR throw "残局格式错误"
        if (!rem.open(QIODevice::ReadOnly)) throw "载入失败";
        QStringList RList = QString(rem.readAll()).split(QRegExp("[\n\r ]"),QString::SkipEmptyParts);
        ChessColor Player,Opp;
        QList<ChessInfo> CList;
        int i;
        auto NX=[=](int& i){if (i+1>=RList.size()) ERR; return ++i;};
        auto getint=[&](){bool ok;int tmp = RList[NX(i)].toInt(&ok);if (!ok) ERR;return tmp;};

        if (RList[0]=="white") Player = ChessColor::WHITE;
        else if (RList[0]=="black") Player = ChessColor::BLACK;
        else ERR;

        bool King = false;
        for (i = 1; i < RList.size(); ++i) {
            ChessType cur;
            if (RList[i] == "king") {cur = ChessType::KING; King = true;}
            else if (RList[i] == "queen") cur = ChessType::QUEEN;
            else if (RList[i] == "bishop") cur = ChessType::BISHOP;
            else if (RList[i] == "knight") cur = ChessType::KNIGHT;
            else if (RList[i] == "rook") cur = ChessType::ROOK;
            else if (RList[i] == "pawn") cur = ChessType::PAWN;
            else if (RList[i] == (Player==ChessColor::WHITE?"black":"white")) break;
            else throw "残局格式错误";
            int k = getint(); if (k <= 0) ERR;
            for (int j = 1; j <= k; ++j) {
                QString spos = RList[NX(i)];
                if (spos.length()!=2) ERR;
                int x = spos.toStdString().at(0)-'a'+1, y = spos.toStdString().at(1)-'0';
                if (1 > x || x > 8 || 1 > y || y > 8) ERR;
                CList.append(ChessInfo(cur,Player,POS(x,y)));
            }
        }

        if (!King) ERR; King = false;
        if (Player == ChessColor::BLACK) {
            if (RList[i] == "white") Opp = ChessColor::WHITE;
            else ERR;
        }
        else {
            if (RList[i] == "black") Opp = ChessColor::BLACK;
            else ERR;
        }

        for (i = NX(i); i < RList.size(); ++i) {
            ChessType cur;
            if (RList[i] == "king") {cur = ChessType::KING; King = true;}
            else if (RList[i] == "queen") cur = ChessType::QUEEN;
            else if (RList[i] == "bishop") cur = ChessType::BISHOP;
            else if (RList[i] == "knight") cur = ChessType::KNIGHT;
            else if (RList[i] == "rook") cur = ChessType::ROOK;
            else if (RList[i] == "pawn") cur = ChessType::PAWN;
            else throw "残局格式错误";
            int k = getint(); if (k <= 0) ERR;
            for (int j = 1; j <= k; ++j) {
                QString spos = RList[NX(i)];
                if (spos.length()!=2) ERR;
                int x = spos.toStdString().at(0)-'a'+1, y = spos.toStdString().at(1)-'0';
                if (1 > x || x > 8 || 1 > y || y > 8) ERR;
                CList.append(ChessInfo(cur,Opp,POS(x,y)));
            }
        }

        firstPlayer = Player;
        CB->receiveMsg(ChessMessage(CList,MsgType::Load));
#undef ERR
    } catch (const char *msg) {
        ErrMsg->showMessage(msg);
    }
    rem.close();
}

void MainWindow::gameStart(ChessConnection *_net)
{
    if (network) return;
    network = _net;
    connect(network,&ChessConnection::messsageReady,[this](ChessMessage Msg){getMsg(Msg);});
    connect(network,&ChessConnection::ruleReceived,[this](int TIME){CB->setTIME_MAX(TIME);});
    if (network->isHost()) network->sendRules(CB->getTIME_MAX());
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();
    ui->action_load->setEnabled(false);
    ui->action_loaddefault->setEnabled(false);
    ui->action_host->setEnabled(false);
    ui->action_connect->setEnabled(false);
    ui->action_save->setEnabled(true);
    ui->pushButton_Submit->setEnabled(true);
    if (network->isHost()) {
        if (firstPlayer == ChessColor::WHITE) {
            sendMsg(ChessMessage(CB->getChessInfoList(),MsgType::Load));
            ui->label_status->setText("行棋");
            CB->startOperating();
            return;
        }
        else sendMsg(ChessMessage(CB->getChessInfoList(),MsgType::Move));
    }
    else {
        CB->Player = ChessColor::BLACK;
    }
    ui->label_status->setText("等待");
}

void MainWindow::sendMsg(const ChessMessage &Msg)
{
    network->sendMsg(Msg);
    switch (Msg.getType()) {
    case MsgType::Win:
        QMessageBox::information(this,"游戏结束","将杀，你输了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Timeout:
        QMessageBox::information(this,"游戏结束","行棋超时，你输了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Submission:
        QMessageBox::information(this,"游戏结束","己方投降，你输了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Draw:
        QMessageBox::information(this,"游戏结束","和局（逼和）",QMessageBox::Ok);
        close();
        break;
    case MsgType::Move:
        ui->label_status->setText("等待");
        break;
    case MsgType::Load:
        break;
    }
}

void MainWindow::getMsg(ChessMessage Msg)
{
    CB->stopOperating();
    switch (Msg.getType()) {
    case MsgType::Win:
        QMessageBox::information(this,"游戏结束","将杀，你赢了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Timeout:
        QMessageBox::information(this,"游戏结束","对方超时，你赢了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Submission:
        QMessageBox::information(this,"游戏结束","对方投降，你赢了！",QMessageBox::Ok);
        close();
        break;
    case MsgType::Draw:
        QMessageBox::information(this,"游戏结束","和局（逼和）",QMessageBox::Ok);
        close();
        break;
    case MsgType::Move:
        ui->label_status->setText("行棋");
        CB->receiveMsg(Msg);
        break;
    case MsgType::Load:
        CB->receiveMsg(Msg);
        break;
    }
}

void MainWindow::on_pushButton_Submit_clicked()
{
    CB->stopOperating();
    sendMsg(ChessMessage(CB->getChessInfoList(),MsgType::Submission));
}


void MainWindow::on_action_save_triggered()
{
    QFile Save(QFileDialog::getSaveFileName());
    if (!(Save.open(QIODevice::WriteOnly))) {
        QMessageBox::warning(this,"保存残局","保存失败",QMessageBox::Ok);
        return;
    }
    Save.write(CB->getRemBoard().toUtf8());
    QMessageBox::information(this,"保存残局","保存成功",QMessageBox::Ok);
}
