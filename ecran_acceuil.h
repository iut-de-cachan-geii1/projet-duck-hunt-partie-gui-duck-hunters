#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include <QDialog>
#include "qserialport.h"
#include "qserialportinfo.h"
#include <QIntValidator>
#include "setting.h"

namespace Ui {
class ecran_acceuil;
}

class ecran_acceuil : public QDialog
{
    Q_OBJECT

public:
    explicit ecran_acceuil(QWidget *parent = nullptr);
    ~ecran_acceuil();
    QString yaw_string,pitch_string,roll_string,fire_string;
    double yaw_double,pitch_double,roll_double,fire;
    int cpt = 0;
    QSerialPort *m_serial = nullptr;
    void attachSettings(setting *fenetre_qui_faut_attacher);

signals : 
    void pseudo_to_send(QString pseudo);
     

private slots:

    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void writeData(const QByteArray &data);
    void readData();
    void apply();
    void setting_fenetre();

    
private:
    void fillPortsInfo();
    Ui::ecran_acceuil *ui;
    QIntValidator *m_intValidator = nullptr;
    setting s;
    //setting *parametre;


};

#endif // ECRAN_ACCEUIL_H
