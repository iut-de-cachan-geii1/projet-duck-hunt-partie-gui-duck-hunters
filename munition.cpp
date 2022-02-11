#include "munition.h"

Munition::Munition()
    : positionMunition(),
      cptMunition(3)
{
    startTimer(1000 / 33);
}

void Munition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (cptMunition == 3)
    {
        QPixmap munition(":/images/3munitions.png");
        painter->drawPixmap(QPoint(0, 0), munition);
    }
    else if (cptMunition == 2)
    {
        QPixmap munition(":/images/2munitions.png");
        painter->drawPixmap(QPoint(0, 0), munition);
    }
    else if (cptMunition == 1)
    {
        QPixmap munition(":/images/1munition.png");
        painter->drawPixmap(QPoint(0, 0), munition);
    }
}

void Munition::timerEvent(QTimerEvent *event)
{
    setPos(100,620);
}
