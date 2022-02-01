#include "crosshair.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QPixmap>

#define Droite 1205
#define Gauche 0
#define Haut 0
#define Bas 600
#define vitesseX 8

static qreal normalizeAngle(qreal angle)
{
    return angle;
}

Crosshair::Crosshair()
{
    startTimer(1000 / 33);
}

QRectF Crosshair::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Crosshair::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 75, 71);
    return path;
}

void Crosshair::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap imageDeCrosshair(":/images/crosshair.png");
    painter->drawPixmap(QPoint(-30, -30), imageDeCrosshair);
}

void Crosshair::timerEvent(QTimerEvent *event)
{
    setPos(coordinateMouse);
}

