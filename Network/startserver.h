#ifndef STARTSERVER_H
#define STARTSERVER_H

#include <QDialog>

namespace Ui {
class StartServer;
}

class StartServer : public QDialog
{
    Q_OBJECT

public:
    explicit StartServer(QWidget *parent = nullptr);
    ~StartServer();

private:
    Ui::StartServer *ui;
};

#endif // STARTSERVER_H
