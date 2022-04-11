#include "setting.h"
#include "ui_setting.h"
#include "qserialport.h"
#include "qserialportinfo.h"

setting::setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(ui->pushButton, &QPushButton::clicked,this, &setting::on_pushButton_clicked);
    connect(ui->list_port, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &setting::checkCustomDevicePathPolicy);
    fillPortsInfo();
    
}

setting::~setting()
{
    delete ui;
}

void setting::checkCustomDevicePathPolicy(int idx)
{
    const bool isCustomPath = !ui->list_port->itemData(idx).isValid();
    ui->list_port->setEditable(isCustomPath);
    if (isCustomPath)
       ui->list_port->clearEditText();
}

void setting::fillPortsInfo()
{
    ui->list_port->clear();

    const auto infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : infos) {
        QStringList list;

        list << info.portName();

        ui->list_port->addItem(list.first(), list);
        
    }
    
}
void setting::on_pushButton_clicked()
{
    nom_port = ui->list_port->currentText();
    hide();
}



void setting::on_musique_valueChanged(int value)
{
    level_musique = value;
    ui->label->setNum(level_musique);
}

void setting::on_effet_sonore_valueChanged(int value)
{
    level_effet_sonore = value;
    ui->label_2->setNum(level_effet_sonore);
}

