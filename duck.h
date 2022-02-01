#ifndef DUCK_H
#define DUCK_H

#include <QGraphicsObject>
#include <QLabel>

class Duck : public QGraphicsObject
{
    Q_OBJECT

public:
    Duck();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    
    void detruireLeCanard();

    QPointF positionDuck;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
    bool canard_tempo = true;
};
#endif
