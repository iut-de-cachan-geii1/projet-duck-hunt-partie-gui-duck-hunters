
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

#include "crosshair.h"
#include "ecran_acceuil.h"
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
#define vitesseX 0

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

constexpr float coeff_teta = Pi / 180.0f;
constexpr float distance_metre = 0.40f; //40
constexpr float coeff_pixel = 3779.5275591f;

Crosshair::Crosshair()
    : fireInTheHole(0),
      pos_x(640),
      pos_y(384)

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

void Crosshair::attach_window(ecran_acceuil *fenetre_qui_faut_attacher)
{
    this->fenetre = fenetre_qui_faut_attacher;
}

void Crosshair::timerEvent(QTimerEvent *event)
{
    // // pos_x = -(fenetre->yaw_double * 23 ) ;
    // // pos_y = -(fenetre->roll_double * 23 ) ;

    // pos_x = -(tan(fenetre->yaw_double * coeff_teta)) * distance_metre * coeff_pixel;
    // pos_y = -(tan(fenetre->roll_double * coeff_teta)) * distance_metre * coeff_pixel;
    // //setPos(coordinateMouse);

    // setPos(QPointF(pos_x + 640, pos_y + 384));

    // fireInTheHole = fenetre->fire;
}