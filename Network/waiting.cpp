#include "waiting.h"
#include "ui_waiting.h"

Waiting::Waiting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Waiting)
{
    ui->setupUi(this);
}

Waiting::~Waiting()
{
    delete ui;
}

void Waiting::setText(QString txt)
{
    ui->label->setText(txt);
}

void Waiting::on_pushButton_clicked()
{
    reject();
}

void Waiting::closeEvent(QCloseEvent *)
{
    reject();
}
