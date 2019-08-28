#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QDialog>

namespace Ui {
class ConnectServer;
}

class ConnectServer : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectServer(QWidget *parent = nullptr);
    ~ConnectServer();

private:
    Ui::ConnectServer *ui;
};

#endif // CONNECTSERVER_H
