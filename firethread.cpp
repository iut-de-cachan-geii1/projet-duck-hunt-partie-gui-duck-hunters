
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

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QPixmap>

#include "firethread.h"
#include "graphicsview.h"

#define decalageLargeur 85 // 75
#define decalageHauteur 78 // 68

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

constexpr float coeff_teta = Pi / 180.0f;
constexpr float distance_metre = 0.40f; //40
constexpr float coeff_pixel = 3779.5275591f;            

void FireThread::run()
{
    while (true)
    {
     viseur->fireInTheHole = ecran->fire;

        if (ecran->m_serial->isOpen())
        {
            if (viseur->fireInTheHole == 1)
            {
                for (int i = 0; i < vue->DuckCount; i++)
                {
                    if (((viseur->pos_x) >= ((ducks->at(i)->positionDuck.rx() - 640)) && ((viseur->pos_x) <= (ducks->at(i)->positionDuck.rx() - 640 + decalageLargeur))))
                    {
                        if (((viseur->pos_y) >= (ducks->at(i)->positionDuck.ry() - 384)) && ((viseur->pos_y) <= (ducks->at(i)->positionDuck.ry() - 384 + decalageHauteur)))
                        {
                            if (ducks->at(i)->cliqueDessus == false)
                            {
                                ducks->at(i)->isDead = true;
                                ducks->at(i)->cliqueDessus = true;
                                (scorus->nombreCanardTue)++;
                                scorus->scoreCpt = scorus->nombreCanardTue * 1;
                                round->roundCpt = scorus->nombreCanardTue / 10;
                            }
                        }
                    }
                }
                (ammunition->cptMunition)--;
                msleep(200);
            }
        }
    }
}
void FireThread::attachCrosshair(Crosshair *viseurQuiFautAttacher)
{
    this->viseur = viseurQuiFautAttacher;
}

void FireThread::attachEcran(ecran_acceuil *fenetre_qui_faut_attacher)
{
    this->ecran = fenetre_qui_faut_attacher;
}

void FireThread::attachDucks(QList<Duck *> *DucksQuiFautAttacher)
{
    this->ducks = DucksQuiFautAttacher;
}

void FireThread::attachAmmo(Munition *munitionQuiFautAttacher)
{
    this->ammunition = munitionQuiFautAttacher;
}
void FireThread::attachScore(Score *scoreQuiFautAttacher)
{
    this->scorus = scoreQuiFautAttacher;
}
void FireThread::attachRound(Round *roundQuiFautAttacher)
{
    this->round = roundQuiFautAttacher;
}
void FireThread::attachVue(GraphicsView *vueQuiFautAttacher)
{
    this->vue = vueQuiFautAttacher;
}
