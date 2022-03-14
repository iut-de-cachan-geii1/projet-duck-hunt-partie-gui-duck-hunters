#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include <QDialog>
#include <QSoundEffect>

namespace Ui {
class ecran_acceuil;
}

class ecran_acceuil : public QDialog
{
    Q_OBJECT

public:
    explicit ecran_acceuil(QWidget *parent = nullptr);
    ~ecran_acceuil();
    
signals : 
    void pseudo_to_send(QString pseudo);

private:
    Ui::ecran_acceuil *ui;
    QSoundEffect pseudo_song;

};

#endif // ECRAN_ACCEUIL_H
