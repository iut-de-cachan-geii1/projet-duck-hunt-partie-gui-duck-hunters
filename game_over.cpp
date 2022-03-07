#include "game_over.h"
#include "ui_game_over.h"

Game_over::Game_over(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game_over)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(ui->rejouer, &QPushButton::clicked, this, 
    
        [this]()
        {
            emit Game_over::perdu();
        }    
    );

    connect(ui->retouraumenu, &QPushButton::clicked, this, 
    
        [this]()
        {
            emit Game_over::return_menu();
        }    
    );
}

Game_over::~Game_over()
{
    delete ui;
}
