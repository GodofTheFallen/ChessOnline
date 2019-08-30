#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QDialog>
#include <QErrorMessage>
#include "chessconnection.h"

namespace Ui {
class ConnectServer;
}

class ConnectServer : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectServer(QWidget *parent = nullptr);
    ~ConnectServer();
    static const int timeout = 10;

signals:
    void genConnection(ChessConnection*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectServer *ui;
    bool status;
    ChessConnection *newConnection;
    void cancel();
    QTimer *Timer;
    int remTime;
};

#endif // CONNECTSERVER_H
