#ifndef PAWNPROMOTION_H
#define PAWNPROMOTION_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class PawnPromotion;
}

class PawnPromotion : public QDialog
{
    Q_OBJECT

public:
    explicit PawnPromotion(QWidget *parent = nullptr);
    ~PawnPromotion();
    Ui::PawnPromotion *ui;

protected:
    void reject();

};

#endif // PAWNPROMOTION_H
