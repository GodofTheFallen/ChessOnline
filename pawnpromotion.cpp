#include "pawnpromotion.h"
#include "ui_pawnpromotion.h"

PawnPromotion::PawnPromotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PawnPromotion)
{
    ui->setupUi(this);
}

PawnPromotion::~PawnPromotion()
{
    delete ui;
}
