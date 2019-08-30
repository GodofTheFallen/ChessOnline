#ifndef GAMESETTING_H
#define GAMESETTING_H

#include <QDialog>

namespace Ui {
class GameSetting;
}

class GameSetting : public QDialog
{
    Q_OBJECT

public:
    explicit GameSetting(QWidget *parent = nullptr);
    ~GameSetting();

signals:
    void settingTime(int);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GameSetting *ui;
};

#endif // GAMESETTING_H
