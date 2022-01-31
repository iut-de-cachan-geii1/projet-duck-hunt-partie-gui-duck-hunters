#include "dialog.ui"
#include "menu.h"
#include <QRadioButton>

Dialog_name::Dialog_name(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_name)
{
    ui->setupUi(this);
    connect(ui->radioButton,&QRadioButton::toggled,this,[this](){
    name=ui->lineEdit->text();
    accept();
    });
}

Dialog_name::~Dialog_name()
{
    delete ui;
}

QString Dialog_name::return_name(){

    return name;


}