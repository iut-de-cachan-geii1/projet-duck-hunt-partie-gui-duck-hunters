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
    player_best = ui->first_player;
    player_best_deuxieme = ui->segundo_playado;
    player_best_troisieme = ui->dritter_spieler;

    player_best_scorus = ui->first_player_2;
    player_best_deuxieme_scorus = ui->segundo_playado_2;
    player_best_troisieme_scorus = ui->dritter_spieler_2;
}

Game_over::~Game_over()
{
    delete ui;
}
