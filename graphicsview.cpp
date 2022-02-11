/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphicsview.h"

#include <QScrollBar>
#include <QTouchEvent>
#include <QRandomGenerator>
#include "ecran_acceuil.h"
#include "duck.h"

#define decalageLargeur 75 // 75
#define decalageHauteur 68 // 68

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent),
      DuckCount(1),
      pos_random(),
      compare(true),
      has_pseudo(false),
      pseudo()
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);
    startTimer(1000 / 500);
    setFixedSize(1280, 769);
    setMouseTracking(true);
    
}

void GraphicsView::attachCrosshair(Crosshair *parametreCrosshair)
{
    this->crosshair = parametreCrosshair;
}
void GraphicsView::attachDucks(QList<Duck *> *DucksQuiFautAttacher)
{
    this->ducks = DucksQuiFautAttacher;
}
void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    crosshair->coordinateMouse = event->pos();
}

void GraphicsView::attach_ecran_acceuil(ecran_acceuil*ecran)
{
    this->ecran = ecran;
    connect(ecran, &ecran_acceuil::pseudo_to_send, this, 

        [this](QString username)            //fonction lambda
        {
            pseudo = username;
            has_pseudo = true;
            this->showNormal();
            this->ecran->hide();
        }
    );
}

//==================BOUM BOUM LE CANARD==================

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        for (int i = 0; i < DuckCount; i++)
        {
            if (((crosshair->coordinateMouse.rx()) >= ((ducks->at(i)->positionDuck.rx())) && ((crosshair->coordinateMouse.rx()) <= (ducks->at(i)->positionDuck.rx() + decalageLargeur))))
            {
                if (((crosshair->coordinateMouse.ry()) >= (ducks->at(i)->positionDuck.ry())) && ((crosshair->coordinateMouse.ry()) <= (ducks->at(i)->positionDuck.ry() + decalageHauteur)))
                {
                    if (ducks->at(i)->cliqueDessus == !compare)
                    {
                        ducks->at(i)->isDead = compare;
                        ducks->at(i)->cliqueDessus = compare;
                    }
                }
            }
        }
    }
}

//==================BOUM BOUM LE CANARD==================

void GraphicsView::timerEvent(QTimerEvent *event)
{
    if (ducks->isEmpty())
    {
        DuckCount = QRandomGenerator::global()->bounded(1, 3);

        for (int i = 0; i < DuckCount; i++)
        {
            ducks->push_back(new Duck);

            this->scene()->addItem(ducks->back());

            pos_random = QRandomGenerator::global()->bounded(300, 900);
            ducks->back()->setPos(pos_random, 570);
        }
    }
    else
    {
        for (int i = 0; i < DuckCount; i++)
        {
            if ((ducks->at(i)->vraimentMort) == compare)
            {
                delete ducks->at(i);
                ducks->removeAt(i);
                (this->DuckCount)--;
            }
        }
    }
}

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
