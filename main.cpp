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
#include "duck.h"
#include "crosshair.h"
#include "munition.h"
#include "score.h"
#include "ecran_acceuil.h"
#include "round.h"
#include "choix_level.h"
#include "game_over.h"

#include <QGraphicsVideoItem>
#include <QRandomGenerator>
#include <QApplication>
#include <cmath>
#include <QPainterPath>
#include <QMediaPlayer>
#include <QList>
#include <fstream>
#include <QSoundEffect>
#include <QMediaPlayer>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    GraphicsView view(&scene);
    QList<Duck *> *listeDeCanard = new QList<Duck *>;
    Crosshair *crosshair = new Crosshair;
    Munition *ammo = new Munition;
    Score *score = new Score;
    Round *round = new Round;
    //Chien *chien = new Chien;

    scene.setSceneRect(0, 0, 1280, 769);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    static int pos_random;

    for (int i = 0; i < view.DuckCount; i++)
    {
        listeDeCanard->push_back(new Duck);

        scene.addItem(listeDeCanard->back());

        pos_random = QRandomGenerator::global()->bounded(100, 1100);
        listeDeCanard->back()->setPos(pos_random, 570);
        listeDeCanard->at(i)->difficulte_coin;
    }
    view.attachDucks(listeDeCanard);

    view.attachDucks(listeDeCanard);

    crosshair->setPos(640, 384);
    ammo->setPos(80, 650);
    score->setPos(250, 670);
    round->setPos(750, 670);
    scene.addItem(crosshair);
    scene.addItem(ammo);
    scene.addItem(score);
    scene.addItem(round);
    //scene.addItem(chien);
    // scene.addRect(0,0,1201,600);

    view.setRenderHint(QPainter::Antialiasing);

    ecran_acceuil pseudo_win;
    pseudo_win.show();
    choix_level choix_niveau;
    Game_over loose;
    view.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    view.attach_ecran_acceuil(&pseudo_win);
    view.attach_choix_level(&choix_niveau);
    view.attach_perdre(&loose);

    // view.setBackgroundBrush(QPixmap(":/images/background.png"));
    // view.setForegroundBrush(QPixmap(":/images/foreground.png"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::QGraphicsView::FullViewportUpdate);

    view.attachCrosshair(crosshair);
    view.attachAmmo(ammo);
    view.attachScore(score);
    view.attachRound(round);
    //view.attachChien(chien);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Duck hunt"));
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setCursor(Qt::BlankCursor);
    
    return QApplication::exec();
}
