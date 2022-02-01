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

#include "duck.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QPixmap>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>

#define Droite 1205
#define Gauche 0
#define Haut 0
#define Bas 600
#define vitesseX 8

static qreal normalizeAngle(qreal angle)
{
    /*while (angle < 0)
    {
        angle += TwoPi;
    }

    while (angle > TwoPi)
    {
        angle -= TwoPi;
    }
*/
    return angle;
}

Duck::Duck()
{
    startTimer(1000 / 33);
}

QRectF Duck::boundingRect() const
{
     qreal adjust = 0.5;
     return QRectF(-18 - adjust, -22 - adjust,
                 36 + adjust, 60 + adjust);
}

QPainterPath Duck::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 75, 71);
    return path;
}

void Duck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    bool compare = true;
    QLineF lineCenterToDestination(QPoint(25, 25), mapFromScene(650, 350));

    //painter->drawLine(lineCenterToDestination);
    /*
    QPixmap imageDeCanard(":/images/canard.png");
    painter->drawPixmap(QPoint(0, 0), imageDeCanard);*/
    if (canard_tempo == compare)
    {
        QPixmap imageDeCanard(":/images/canard1.png");
        painter->drawPixmap(QPoint(0, 0), imageDeCanard);
    }
    else
    {
        QPixmap imageDeCanard(":/images/canard2.png");
        painter->drawPixmap(QPoint(0, 0), imageDeCanard);
    }
}

void Duck::detruireLeCanard()
{
    delete this;
}

void Duck::timerEvent(QTimerEvent *event)
{
    static int cpt = 0;
    cpt++;

    if (cpt == 7)
    {
        canard_tempo = !canard_tempo;
        cpt = 0;
    }

    QPointF pos_actuelle = pos();
    positionDuck = pos_actuelle;
    QPointF position_target(1200, 200);
    static int directionX = QRandomGenerator::global()->bounded(0, 2); //si 1 va a gauche, si 0 va a droitre
    static int directionY = 1;                                         //si 1 va en haut, si 0 va en bas
    static int hauteur_rng = QRandomGenerator::global()->bounded(2, 9);

    if ((directionX == 1) && (directionY == 1)) // va en haut vers la gauche
    {
        if (pos_actuelle.rx() <= 0)
        {
            directionX = 0;
        }
        else if (pos_actuelle.ry() <= 0)
        {
            directionY = 0;
        }
        else
        {
            setPos(pos_actuelle + QPointF(-vitesseX, -hauteur_rng));
        }
    }
    if ((directionX == 0) && (directionY == 1)) //Va en haut a droite
    {
        if (pos_actuelle.rx() >= 1200)
        {
            directionX = 1;
        }
        else if (pos_actuelle.ry() <= 0)
        {
            directionY = 0;
        }
        else
        {
            setPos(pos_actuelle + QPointF(vitesseX, -hauteur_rng));
        }
    }

    if ((directionX == 1) && (directionY == 0)) //va en bas a gauche
    {
        if (pos_actuelle.rx() <= 0)
        {
            directionX = 0;
        }
        else if (pos_actuelle.ry() >= 540)
        {
            directionY = 1;
        }
        else
        {
            setPos(pos_actuelle + QPointF(-vitesseX, hauteur_rng));
        }
    }
    if ((directionX == 0) && (directionY == 0)) //va en bas a droite
    {
        if (pos_actuelle.rx() >= 1200)
        {
            directionX = 1;
        }
        else if (pos_actuelle.ry() >= 540)
        {
            directionY = 1;
        }
        else
        {
            setPos(pos_actuelle + QPointF(vitesseX, hauteur_rng));
        }
    }
}
