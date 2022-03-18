#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include <QDialog>
#include "qserialport.h"
#include "qserialportinfo.h"
#include <QIntValidator>

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
    
signals : 
    void pseudo_to_send(QString pseudo);

private slots:

    void checkCustomDevicePathPolicy(int idx);
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void writeData(const QByteArray &data);
    void readData();

private:
    void fillPortsInfo();
    Ui::ecran_acceuil *ui;
    QIntValidator *m_intValidator = nullptr;
    QSerialPort *m_serial = nullptr;
};

#endif // ECRAN_ACCEUIL_H
