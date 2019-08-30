#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include "chessboard.h"
#include "gamesetting.h"
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

    void on_action_setting_triggered();

    void on_action_load_triggered();

    void gameStart(ChessConnection *);

    void sendMsg(const ChessMessage &);

    void getMsg(ChessMessage);

    void on_pushButton_Submit_clicked();

    void on_action_loaddefault_triggered();

    void on_action_save_triggered();

private:
    Ui::MainWindow *ui;

    ChessBoard *CB;

    ChessColor firstPlayer;

    ChessConnection *network;

    QErrorMessage *ErrMsg;
};

#endif // MAINWINDOW_H
