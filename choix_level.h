#ifndef CHOIX_LEVEL_H
#define CHOIX_LEVEL_H

#include <QDialog>
#include <QCommonStyle>

namespace Ui {
class choix_level;
}

class choix_level : public QDialog
{
    Q_OBJECT

public:
    explicit choix_level(QWidget *parent = nullptr);
    ~choix_level();

private:
    Ui::choix_level *ui;
};

#endif // CHOIX_LEVEL_H
