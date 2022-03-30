#include "ecran_acceuil.h"
#include "setting.h"
#include "ui_ecran_acceuil.h"
#include "QPushButton"
#include <QMessageBox>
#include "qserialport.h"
#include "qserialportinfo.h"
#include <QIntValidator>
#include <QMessageBox>

ecran_acceuil::ecran_acceuil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ecran_acceuil),
    m_intValidator(new QIntValidator(0, 4000000, this)),
    m_serial(new QSerialPort(this))
{
    ui->setupUi(this);
    connect(m_serial, &QSerialPort::errorOccurred, this, &ecran_acceuil::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &ecran_acceuil::readData);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(ui->enter_button, &QPushButton::clicked, this,

        [this]()
        {
            emit ecran_acceuil::pseudo_to_send(ui->pseudo->text());
        }    
    );

    connect(ui->enter_button, &QPushButton::clicked,this, &ecran_acceuil::apply);
    connect(ui->setting, &QPushButton::clicked,this, &ecran_acceuil::setting_fenetre);
    //fillPortsInfo();
}

ecran_acceuil::~ecran_acceuil()
{   
    delete ui;
}


void ecran_acceuil::setting_fenetre()
{
    s.show();
}

void ecran_acceuil::apply()
{
    openSerialPort();
    readData();
}

void ecran_acceuil::openSerialPort()
{
    m_serial->setPortName(s.nom_port);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
       // m_console->setEnabled(true);

    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

    }
}

void ecran_acceuil::closeSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
    }
}

void ecran_acceuil::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();

    }
}

void ecran_acceuil::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

void ecran_acceuil::readData()
{

    QByteArray recue = m_serial->readLine();
    QString data_string = QString(recue);

    QStringList list = data_string.split("/");

    QStringList list_yaw  = list.filter("Y");
    list_yaw = list_yaw.replaceInStrings("Y","");

    QStringList list_pitch  = list.filter("P");
    list_pitch = list_pitch.replaceInStrings("P","");

    QStringList list_roll  = list.filter("R");
    list_roll = list_roll.replaceInStrings("R","");

    QStringList list_fire  = list.filter("F");
    list_fire = list_fire.replaceInStrings("F","");


    for (int i = 0; i < list_yaw.size(); ++i)
    {
        yaw_string = list_yaw.at(i).toLocal8Bit().constData();
        yaw_double = yaw_string.split(" ")[0].toDouble();
    }

    for (int i = 0; i < list_pitch.size(); ++i)
    {
        pitch_string=list_pitch.at(i).toLocal8Bit().constData();
        pitch_double = pitch_string.split(" ")[0].toDouble();
    }

    for (int i = 0; i < list_roll.size(); ++i)
    {
        roll_string=list_roll.at(i).toLocal8Bit().constData();
        roll_double = roll_string.split(" ")[0].toDouble();
    }

    for (int i = 0; i < list_fire.size(); ++i)
    {
        fire_string=list_fire.at(i).toLocal8Bit().constData();
        fire = fire_string.split(" ")[0].toInt();

    }

    (void)0;

}


