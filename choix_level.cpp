#include "choix_level.h"
#include "ui_choix_level.h"


choix_level::choix_level(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choix_level)
{
    ui->setupUi(this);


}

choix_level::~choix_level()
{
    delete ui;
}
