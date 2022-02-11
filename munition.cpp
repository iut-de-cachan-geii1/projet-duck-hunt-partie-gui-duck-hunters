#include "munition.h"

Munition::Munition()
    : positionMunition(),
      cptMunition(3)
{
    startTimer(1000 / 33);
}

QRectF Munition::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Munition::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 75, 71);
    return path;
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
    
}
