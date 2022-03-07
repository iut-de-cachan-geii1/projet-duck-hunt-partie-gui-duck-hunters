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
#include "QPushButton"
#include "choix_level.h"
#include "ui_choix_level.h"
#include "game_over.h"

#include <string>
#include <QString>

#define decalageLargeur 75 // 75
#define decalageHauteur 68 // 68

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent),
      DuckCount(1),
      pos_random(),
      compare(true),
      has_pseudo(false),
      pseudo(),
      maps(0),
      levels(0),
      vraiment_perdu(false)
    //   sauvegarde("sauvegarde.json")
      
{
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);
    startTimer(1000 / 500);
    setFixedSize(1280, 769);
    setMouseTracking(true);
    QCursor cursor(Qt::BlankCursor);
    // sauvegarde<<"pseudo : "<<"Hello World !"<<"\n";
    // sauvegarde.close();
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
void GraphicsView::attachAmmo(Munition *munitionQuiFautAttacher)
{
    this->ammo = munitionQuiFautAttacher;
}
void GraphicsView::attachScore(Score *scoreQuiFautAttacher)
{
    this->score = scoreQuiFautAttacher;
}
// void GraphicsView::attachChien(Chien *chienQuiFautAttacher)
// {
//     this->chien = chienQuiFautAttacher;
// }
void GraphicsView::attachRound(Round *roundQuiFautAttacher)
{
    this->round = roundQuiFautAttacher;
}

void GraphicsView::attach_ecran_acceuil(ecran_acceuil *ecran)
{
    this->ecran = ecran;
    connect(ecran, &ecran_acceuil::pseudo_to_send, this,

            [this](QString username) // fonction lambda
            {
                pseudo = username;
                has_pseudo = true;
                this->level->showNormal();
                this->ecran->hide();
            });
}

void GraphicsView::attach_choix_level(choix_level *level)
{
    this->level = level;

    connect(level, &choix_level::map_to_send, this,

            [this](int map_choix) // fonction lambda
            {
                maps = map_choix;
                score->scoreCpt = 0;

            for (int i = 0; i < DuckCount; i++)
                {  
                    delete ducks -> at(i);
                    ducks -> removeAt(i);
                   
                }

            for (int i = 0; i < DuckCount; i++)
                {  
                    ducks->push_back(new Duck);

                    this->scene()->addItem(ducks->back());

                    pos_random = QRandomGenerator::global()->bounded(300, 900);
                    ducks->back()->setPos(pos_random, 570);
                } 

                if (maps == 0)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground.png"));
                }
                if (maps == 1)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background_momo.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground_momo.png"));
                }
                if (maps == 2)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background_nuit.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground_nuit.png"));
                }
                this->level->hide();
                this->showNormal();
            });

    connect(level, &choix_level::level_to_send, this,

            [this](int level_choix) // fonction lambda
            {
                level_choix = levels;
                if (level_choix == 0)
                {
                  
                }
                if (level_choix == 1)
                {
                    
                }
                if (level_choix == 2)
                {
                   
                }
                this->level->hide();
                this->showNormal();
            });
}

void GraphicsView::attach_perdre(Game_over *looser)
{
    loose = looser;

     connect(loose, &Game_over::perdu, this,

            [this]() // fonction lambda
            {
                this->showNormal();
                this->loose->hide();
                ammo->cptMunition = 3;
                score->scoreCpt = 0;

                for (int i = 0; i < DuckCount; i++)
                {  
                    delete ducks -> at(i);
                    ducks -> removeAt(i);
                   
                }

            for (int i = 0; i < DuckCount; i++)
                {  
                    ducks->push_back(new Duck);

                    this->scene()->addItem(ducks->back());

                    pos_random = QRandomGenerator::global()->bounded(300, 900);
                    ducks->back()->setPos(pos_random, 570);
                } 

            });
    
     connect(loose, &Game_over::return_menu, this,

            [this]() // fonction lambda
            {
                this->loose->hide();  
                this->level->showNormal();
                ammo->cptMunition = 3;
            });
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
                        (score->nombreCanardTue)++;
                        score->scoreCpt = score->nombreCanardTue * 1;
                        round->roundCpt = score->nombreCanardTue / 10;
                    }
                }
            }
        }
        (ammo->cptMunition)--;
    }
}

//==================BOUM BOUM LE CANARD==================

void GraphicsView::timerEvent(QTimerEvent *event)
{
    if (ducks->isEmpty() /*&& (chien->chien_fini == true)*/)
    {
        DuckCount = QRandomGenerator::global()->bounded(1, 3);
        ammo->cptMunition = 3;

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
            if (ducks->at(i)->vraimentMort)
            {
                if (ducks->size() == 1)
                {
                    //chien->positionChien = ducks->at(i)->positionDuck + QPointF(0, 0);
                    //chien->tout_les_canards_sont_mort = true;
                }
                delete ducks->at(i);
                ducks->removeAt(i);
                (this->DuckCount)--;
            }
        }
    }

    if ((ammo->cptMunition <= 0) && (ducks->size() >= 1) && (ducks->at(0)->isDead == false) && (ducks->at(0)->isDead2 == false) && (ducks->at(0)->vraimentMort == false))
    {
        loose->show();
        this->hide();
    }
}

bool GraphicsView::viewportEvent(QEvent *event)
{
    
    return QGraphicsView::viewportEvent(event);
}
