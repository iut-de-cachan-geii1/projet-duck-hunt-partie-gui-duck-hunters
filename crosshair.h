#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <QGraphicsObject>
#include <QLabel>

class Crosshair : public QGraphicsObject
{
    Q_OBJECT

public:
    Crosshair();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPointF coordinateMouse;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    
};

#endif
