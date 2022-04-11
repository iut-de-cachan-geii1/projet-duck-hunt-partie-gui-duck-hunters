#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>

namespace Ui {
class setting;
}

class setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    void fillPortsInfo();
    void checkCustomDevicePathPolicy(int idx);
    void on_pushButton_clicked();
    QString nom_port;
    float level_musique, level_effet_sonore;
    
private:
    Ui::setting *ui;

private slots:
    void on_musique_valueChanged(int value);
    
    void on_effet_sonore_valueChanged(int value);
    
};

#endif // SETTING_H
