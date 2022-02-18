#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QDialog>

namespace Ui {
class Game_over;
}

class Game_over : public QDialog
{
    Q_OBJECT

public:
    explicit Game_over(QWidget *parent = nullptr);
    ~Game_over(); 

signals : 
    void perdu();

private:
    Ui::Game_over *ui;
};

#endif // GAME_OVER_H
