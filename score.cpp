#include "munition.h"

Munition::Munition()
    : positionScore(),
      cptSCore(0)
{
    startTimer(1000 / 33);
}

QRectF Score::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Score::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 75, 71);
    return path;
}

void Score::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLabel *label = new QLabel(this);

}

void Score::timerEvent(QTimerEvent *event)
{
    
}
