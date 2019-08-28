#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessboard.h"
#include "Network/chessconnection.h"
#include "Network/startserver.h"
#include "Network/connectserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_host_triggered();

    void on_action_connect_triggered();

    void onServeruiAccept();

    void onConnectuiAccept();



private:
    Ui::MainWindow *ui;
    ChessBoard CB;

    StartServer *serverUi;
    ConnectServer *connectUi;

    ChessConnection network;
};

#endif // MAINWINDOW_H
