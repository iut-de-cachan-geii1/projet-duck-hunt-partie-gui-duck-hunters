#pragma once
#include <QGraphicsView>
#include "crosshair.h"
#include "duck.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = nullptr, QWidget *parent = nullptr);
    void attachCrosshair(Crosshair *parametreCrosshair);
    void attachDuck(Duck *DuckQuiFautAttacher);
    void mouseMoveEvent(QMouseEvent *event) override;

    bool viewportEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    qreal totalScaleFactor = 1;
    Crosshair* crosshair;
    Duck *duck;
};
