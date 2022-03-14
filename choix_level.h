#ifndef CHOIX_LEVEL_H
#define CHOIX_LEVEL_H

#include <QDialog>
#include <QCommonStyle>
#include <QSoundEffect>

namespace Ui {
class choix_level;
}

class choix_level : public QDialog
{
    Q_OBJECT

public:
    explicit choix_level(QWidget *parent = nullptr);
    ~choix_level();
    int numero_map;
    int numero_diff;


private:
    Ui::choix_level *ui;
    QSoundEffect click;

signals :
    void map_to_send(int maps);
    void level_to_send(int levels);

};

#endif // CHOIX_LEVEL_H
