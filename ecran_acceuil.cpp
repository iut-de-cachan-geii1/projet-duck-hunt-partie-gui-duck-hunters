#include "ecran_acceuil.h"
#include "ui_ecran_acceuil.h"
#include "QPushButton"


ecran_acceuil::ecran_acceuil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ecran_acceuil)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(ui->enter_button, &QPushButton::clicked, this, 
    
        [this]()
        {
            emit ecran_acceuil::pseudo_to_send(ui->pseudo->text());
        }    
    );
}

ecran_acceuil::~ecran_acceuil()
{   
    delete ui;
}
