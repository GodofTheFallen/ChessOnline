#ifndef WAITING_H
#define WAITING_H

#include <QDialog>

namespace Ui {
class Waiting;
}

class Waiting : public QDialog
{
    Q_OBJECT

public:
    explicit Waiting(QWidget *parent = nullptr);
    ~Waiting();

private slots:
    void on_pushButton_clicked();

public slots:
    void setText(QString);

private:
    Ui::Waiting *ui;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WAITING_H
