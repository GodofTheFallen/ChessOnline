#ifndef STARTSERVER_H
#define STARTSERVER_H

#include <QDialog>
#include "chessconnection.h"

namespace Ui {
class StartServer;
}

class StartServer : public QDialog
{
    Q_OBJECT

public:
    explicit StartServer(QWidget *parent = nullptr);
    ~StartServer();

signals:
    void genConnection(ChessConnection*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartServer *ui;
    bool status;
    ChessConnection *newConnection;
    void cancel();
    QTimer *Timer;
    int remTime;
};

#endif // STARTSERVER_H
