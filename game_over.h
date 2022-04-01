#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class Game_over;
}

class Game_over : public QDialog
{
    Q_OBJECT

public:
    explicit Game_over(QWidget *parent = nullptr);
    ~Game_over(); 
    QLabel *player_best;
    QLabel *player_best_deuxieme;
    QLabel *player_best_troisieme;

    QLabel *player_best_scorus;
    QLabel *player_best_deuxieme_scorus;
    QLabel *player_best_troisieme_scorus;

signals : 
    void perdu();
    void return_menu();
    
private:
    Ui::Game_over *ui;
};

#endif // GAME_OVER_H
