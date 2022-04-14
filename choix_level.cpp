#include "choix_level.h"
#include "ui_choix_level.h"


choix_level::choix_level(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choix_level),
    numero_map(0),
    numero_diff(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    click.setSource(QUrl::fromUserInput("qrc:/images/click_wii.wav"));
    click.setLoopCount(0);
    click.setVolume(0.99f);
     connect(ui->enter_button, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            emit choix_level::level_to_send(numero_diff);
            emit choix_level::map_to_send(numero_map);
            
        }    
    );
    connect(ui->right_map, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            numero_map ++;

            if(numero_map == 0)
            {
                ui->map->setPixmap(QPixmap(":/images/stage.png"));
            }
            if(numero_map == 1)
            {
                ui->map->setPixmap(QPixmap(":/images/background_momo_menu.png"));
            }
            if(numero_map == 2)
            {
                ui->map->setPixmap(QPixmap(":/images/background_nuit_menu.png"));
            }
            if(numero_map == 3)
            {
                ui->map->setPixmap(QPixmap(":/images/map_blyat_mini.png"));
            }
            if(numero_map == 4)
            {
                numero_map = 0;
                ui->map->setPixmap(QPixmap(":/images/stage.png"));
            }
           //emit choix_level::map_to_send(numero_map);
        }    
    );
    connect(ui->left_map, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            numero_map --;

           
            if(numero_map == 0)
            {
                ui->map->setPixmap(QPixmap(":/images/stage.png"));
            }
            if(numero_map == 1)
            {
                ui->map->setPixmap(QPixmap(":/images/background_momo_menu.png"));
            }
            if(numero_map == 2)
            {
                ui->map->setPixmap(QPixmap(":/images/background_nuit_menu.png"));
            }
            if(numero_map == 3)
            {
                ui->map->setPixmap(QPixmap(":/images/background_nuit_menu.png"));
            }
            if(numero_map == -1)
            {
                numero_map = 3;
                ui->map->setPixmap(QPixmap(":/images/map_blyat_mini.png"));
            }
        // emit choix_level::map_to_send(numero_map);
        }    
    );

    connect(ui->left_difficulte, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            numero_diff --;

        
            
            if(numero_diff == 0)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_facile.png"));
            }
            if(numero_diff == 1)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_medium.png"));
            }
            if(numero_diff == 2)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_difficile.png"));
            }
            if(numero_diff == -1)
            {
                numero_diff = 2;
                ui->difficulte->setPixmap(QPixmap(":/images/mode_difficile.png"));
            }
         //emit choix_level::level_to_send(numero_diff);
        }    
    );

    connect(ui->right_difficulte, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            numero_diff ++;

            
            if(numero_diff == 0)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_facile.png"));
            }
            if(numero_diff == 1)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_medium.png"));
            }
            if(numero_diff == 2)
            {
                ui->difficulte->setPixmap(QPixmap(":/images/mode_difficile.png"));
            }
            if(numero_diff == 3)
            {
                numero_diff = 0;
                ui->difficulte->setPixmap(QPixmap(":/images/mode_facile.png"));
               
            }
            
        
        }    
    );

    connect(ui->mode_doom, &QPushButton::clicked, this, 
    
        [this]()
        {
            click.play();
            emit choix_level::map_to_send(numero_map = 666);
            emit choix_level::level_to_send(numero_diff = 3); 
        }
    );


}



choix_level::~choix_level()
{
    delete ui;
}
