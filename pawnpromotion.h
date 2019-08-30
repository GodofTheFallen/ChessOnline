#ifndef PAWNPROMOTION_H
#define PAWNPROMOTION_H

#include <QDialog>

namespace Ui {
class PawnPromotion;
}

class PawnPromotion : public QDialog
{
    Q_OBJECT

public:
    explicit PawnPromotion(QWidget *parent = nullptr);
    ~PawnPromotion();

private:
    Ui::PawnPromotion *ui;
};

#endif // PAWNPROMOTION_H
