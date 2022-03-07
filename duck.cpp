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

#define Droite 1205
#define Gauche 0
#define Haut 0
#define Bas 600
#define vitesseX 10

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
:   positionDuck(),
    isDead(false),
    isDead2(false),
    vraimentMort(false),
    cliqueDessus(false),
    angle(0),
    speed(0),
    mouseEyeDirection(0),
    color(),
    canard_tempo(true),
    canard_rotate(true),
    canard_sens(false),
    cpt(0),
    cptMort(0),
    directionX(QRandomGenerator::global()->bounded(0, 2)), //si 1 va a gauche, si 0 va a droitre
    directionY(1),                                       //si 1 va en haut, si 0 va en bas
    hauteur_rng(QRandomGenerator::global()->bounded(2, 11)),
    compare(true)
  
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
    // QLineF lineCenterToDestination(QPoint(0, 0), mapFromScene(650, 350));
    // painter->drawLine(lineCenterToDestination);
    if (isDead == compare)
    {
        QPixmap imageDeCanard(":/images/canard_mort.png");
        painter->drawPixmap(QPoint(0, 0), imageDeCanard);
    }
    else
    {
        if (isDead2 == !compare)
        {
            if (canard_tempo == compare) // tempo qui change le sprite du canard regulierement pour donner
            {                            //l'illusion qu'il bat des ailes
                if (canard_sens == compare) 
                {
                    QPixmap imageDeCanard(":/images/canard1.png");
                    painter->drawPixmap(QPoint(0, 0), imageDeCanard);
                }
                else
                {
                    QPixmap imageDeCanard(":/images/canard1_inverse.png");
                    painter->drawPixmap(QPoint(0, 0), imageDeCanard);
                }
            }
            else
            {
                if (canard_sens == compare)
                {
                    QPixmap imageDeCanard(":/images/canard2.png");
                    painter->drawPixmap(QPoint(0, 0), imageDeCanard);
                }
                else
                {
                    QPixmap imageDeCanard(":/images/canard2_inverse.png");
                    painter->drawPixmap(QPoint(0, 0), imageDeCanard);
                }
            }
        }
        else
        {
            if (canard_tempo == compare) // tempo qui change le sprite du canard regulierement pour donner
            {
                QPixmap imageDeCanard(":/images/canard_mort_tombe.png");
                painter->drawPixmap(QPoint(0, 0), imageDeCanard);
            }
            else
            {
                QPixmap imageDeCanard(":/images/canard_mort_tombe_inverse.png");
                painter->drawPixmap(QPoint(0, 0), imageDeCanard);
            }
        }
    }
}


void Duck::timerEvent(QTimerEvent *event)
{
    (this->cpt)++;

    if ((this->cpt) == 7) //diviser l'horloge du timer par 7 pour battre des ailes moins vite
    {
        canard_tempo = !canard_tempo;
        (this->cpt) = 0;
    }
     
    QPointF pos_actuelle = pos();
    this->positionDuck = pos_actuelle;

    if ((directionX == 1) && (directionY == 1) && (isDead == !compare)) // va en haut vers la gauche
    {
        canard_sens = false;
        if (pos_actuelle.rx() <= 0)
        {
            directionX = 0;
            canard_sens = !canard_sens;
        }
        else if (pos_actuelle.ry() <= 0)
        {
            directionY = 0;
        }
        else
        {
            setPos(pos_actuelle + QPointF(-vitesseX , -hauteur_rng));
        }
    }
    if ((directionX == 0) && (directionY == 1) && (isDead == !compare)) //Va en haut a droite
    {
        canard_sens = true;
        if (pos_actuelle.rx() >= 1200)
        {
            directionX = 1;
            canard_sens = !canard_sens;
        }
        else if (pos_actuelle.ry() <= 0)
        {
            directionY = 0;
        }
        else
        {
            setPos(pos_actuelle + QPointF(vitesseX , -hauteur_rng));
        }
    }

    if ((directionX == 1) && (directionY == 0) && (isDead == !compare)) //va en bas a gauche
    {
        if (pos_actuelle.rx() <= 0)
        {
            directionX = 0;
            canard_sens = !canard_sens;
        }
        else if (pos_actuelle.ry() >= 540)
        {
            directionY = 1;
        }
        else
        {
            setPos(pos_actuelle + QPointF(-vitesseX , hauteur_rng));
        }
    }
    if ((directionX == 0) && (directionY == 0) && (isDead == !compare)) //va en bas a droite
    {
        if (pos_actuelle.rx() >= 1200)
        {
            directionX = 1;
            canard_sens = !canard_sens;
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
    if ((isDead == compare) && (isDead2 == !compare))
    {
        cptMort++;
        if (cptMort == 12)
        {
            isDead2 = true;
            isDead = false;
            cptMort = 0;
        }
    }
    if ((isDead == !compare) && (isDead2 == compare))
    {
        if (pos_actuelle.ry() <= 560)
        {
            setPos(pos_actuelle + QPointF(0, 8));
        }
        else
        {
            isDead2 = false;
            isDead = true;
            vraimentMort = compare;
        }
    }
}
