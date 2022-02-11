#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include <QDialog>

namespace Ui {
class ecran_acceuil;
}

class ecran_acceuil : public QDialog
{
    Q_OBJECT

public:
    explicit ecran_acceuil(QWidget *parent = nullptr);
    ~ecran_acceuil();

protected :
    void press_button();

signals : 
    void pseudo_to_send(QString pseudo);

private:
    Ui::ecran_acceuil *ui;
};

#endif // ECRAN_ACCEUIL_H
