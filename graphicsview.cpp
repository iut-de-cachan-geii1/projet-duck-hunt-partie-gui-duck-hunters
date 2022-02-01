#include "graphicsview.h"

#include <QScrollBar>
#include <QTouchEvent>

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);
    startTimer(1000/500);
    setFixedSize(1280,769);
    setMouseTracking(true);
}

void GraphicsView::attachCrosshair(Crosshair *parametreCrosshair)
{
    this-> crosshair = parametreCrosshair;
}
void GraphicsView::attachDuck(Duck *DuckQuiFautAttacher)
{
    this-> duck = DuckQuiFautAttacher;
}
void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    crosshair -> coordinateMouse = event->pos();
}

//============BOUM BOUM LE CANARD============

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if((crosshair-> coordinateMouse) == (duck->positionDuck))
    {
        duck -> detruireLeCanard();
    }
}

//============BOUM BOUM LE CANARD============

bool GraphicsView::viewportEvent(QEvent *event)
{
    /*
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 2)
        {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
           if ( (touchEvent->touchPointStates() & Qt::TouchPointReleased) != 0u)
            {
                // if one of the fingers is released, remember the current scale
                // factor so that adding another finger later will continue zooming
                // by adding new scale factor to the existing remembered value.
                totalScaleFactor *= currentScaleFactor;
                currentScaleFactor = 1;
            }
            setTransform(QTransform::fromScale(totalScaleFactor * currentScaleFactor,
                                               totalScaleFactor * currentScaleFactor));
        }
        return true;
    }
    default:
        break;
    }*/
    return QGraphicsView::viewportEvent(event);
}

