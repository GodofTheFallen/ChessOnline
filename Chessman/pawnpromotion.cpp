#include "pawnpromotion.h"
#include "ui_pawnpromotion.h"

PawnPromotion::PawnPromotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PawnPromotion)
{
    ui->setupUi(this);
    setWindowTitle("选择升变为");
    setWindowFlags((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint);
}

PawnPromotion::~PawnPromotion()
{
    delete ui;
}

void PawnPromotion::reject()
{
    return;
}


