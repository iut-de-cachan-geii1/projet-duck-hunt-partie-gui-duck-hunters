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

#include <QString>
#include <QSoundEffect>
#include <fstream>
#include <string>
#include <iostream>
#include <QTimer>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <QtMultimedia/QMediaPlayer>
#include <sstream>

namespace fs = std::filesystem;
#include <math.h>

#define decalageLargeur 85 // 75
#define decalageHauteur 78 // 68

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent),
      DuckCount(QRandomGenerator::global()->bounded(1, 3)),
      pos_random(),
      compare(true),
      has_pseudo(false),
      pseudo(),
      maps(0),
      levels(0),
      vraiment_perdu(false),
      difficulte(1),
      timer_escape(new QTimer(this)),
      looseByEscape(false),
      writed(true),
      path(fs::temp_directory_path())

{
    connect(timer_escape, &QTimer::timeout, this, GraphicsView::escapadeDesCanards);
    timer_escape->start(10000);

    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);
    startTimer(1000 / 33);
    setFixedSize(1280, 769);
    setMouseTracking(true);
    QCursor cursor(Qt::BlankCursor);
    panpan.setSource(QUrl::fromUserInput("qrc:/images/oui_tir.wav"));
    panpan.setLoopCount(0);
    panpan.setVolume(0.99f);
    dead.setSource(QUrl::fromUserInput("qrc:/images/canard_dead.wav"));
    dead.setLoopCount(0);
    dead.setVolume(0.99f);
    urss_miam.setSource(QUrl::fromUserInput("qrc:/images/urss_song.wav"));
    urss_miam.setLoopCount(QSoundEffect::Infinite);
    urss_miam.setVolume(0.55f);
    momo_sound.setSource(QUrl::fromUserInput("qrc:/images/desert_song.wav"));
    momo_sound.setLoopCount(QSoundEffect::Infinite);
    momo_sound.setVolume(0.70f);
    // save >> myJson;
    //  val = myJson["1er"];

    // valeur = myJson["1er"];
    // valeur = myJson["name"];

    // std::stringstream buffer;
    // buffer << save.rdbuf();
    // valeur = buffer.str();
    // sauvegarde<<"pseudo : "<<"Hello World !"<<"\n";
    // sauvegarde.close();
}

void GraphicsView::escapadeDesCanards()
{
    for (int i = 0; i < DuckCount; i++)
    {
        ducks->at(i)->canardEscape = true;
    }
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
void GraphicsView::attachChien(Chien *chienQuiFautAttacher)
{
    this->chien = chienQuiFautAttacher;
}
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
                this->level->showNormal();
                this->ecran->hide();
                choose_map_song.setSource(QUrl::fromUserInput("qrc:/images/elevator_song.wav"));
                choose_map_song.setLoopCount(QSoundEffect::Infinite);
                choose_map_song.setVolume(0.1);
                choose_map_song.play();
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
                score->nombreCanardTue = 0;
                round->roundCpt = 0;

                if (ducks->size() == 2)
                {
                    delete ducks->at(1);
                    ducks->removeAt(1);
                    delete ducks->at(0);
                    ducks->removeAt(0);
                }
                else if (ducks->size() == 1)
                {
                    delete ducks->at(0);
                    ducks->removeAt(0);
                }
                //chien->nb_chien = DuckCount;//signed by robbie_le_renneTM

                for (int i = 0; i < DuckCount; i++)
                {
                    ducks->push_back(new Duck);

                    connect(ducks->back(), &Duck::canardVraimentMort, this, &GraphicsView::lesCanardsDoiventRespawn);

                    this->scene()->addItem(ducks->back());

                    pos_random = QRandomGenerator::global()->bounded(300, 900);
                    ducks->back()->setPos(pos_random, 570);

                    ducks->at(i)->difficulte_coin = difficulte;

                    ducks->at(i)->difficulte_round = ducks->at(i)->difficulte_round + round->roundCpt / 10;
                }
                looseByEscape = false;
                timer_escape->start(10000);

                if (maps == 0)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground.png"));
                }
                if (maps == 1)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background_momo.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground_momo.png"));
                    momo_sound.play();
                }
                if (maps == 2)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background_nuit.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground_nuit.png"));
                }
                if (maps == 3)
                {
                    this->setBackgroundBrush(QPixmap(":/images/background_blyat2.png"));
                    this->setForegroundBrush(QPixmap(":/images/foreground_blyat2.png"));
                    urss_miam.play();
                }
                if (maps == 666)
                {
                    this->setBackgroundBrush(QPixmap(":/images/hell_background.jpg"));
                    this->setForegroundBrush(QPixmap(""));
                }
                this->level->hide();
                this->showNormal();
                choose_map_song.stop();
            });

    connect(level, &choix_level::level_to_send, this,

            [this](int level_choix) // fonction lambda
            {
                levels = level_choix;
                if (level_choix == 0)
                {
                    difficulte = 1;
                }
                else if (level_choix == 1)
                {
                    difficulte = 1.33;
                }
                else if (level_choix == 2)
                {
                    difficulte = 1.66;
                }
                else if (level_choix == 3)
                {
                    difficulte = 1.66;
                }
                this->level->hide();
                this->showNormal();
            });
}

void GraphicsView::lesCanardsDoiventRespawn(Duck *canardATuer)
{
    for (int i = 0; i < DuckCount; i++)
    {
        if (canardATuer == ducks->at(i))
        {
            if (canardATuer->isCanardEscaped == true)
            {
                looseByEscape = true;
            }
            delete ducks->at(i);
            ducks->removeAt(i);
            (this->DuckCount)--;
        }
    }
    if (ducks->isEmpty())
    {
        ammo->cptMunition = 3;
        DuckCount = QRandomGenerator::global()->bounded(1, 3);
        //chien->nb_chien = DuckCount;
        //chien->tout_les_canards_sont_mort = true;

        for (int i = 0; i < DuckCount; i++)
        {
            ducks->push_back(new Duck);
            connect(ducks->back(), &Duck::canardVraimentMort, this, &GraphicsView::lesCanardsDoiventRespawn);
            this->scene()->addItem(ducks->back());

            pos_random = QRandomGenerator::global()->bounded(300, 900);
            ducks->back()->setPos(pos_random, 570);

            ducks->at(i)->difficulte_coin = difficulte;

            ducks->at(i)->difficulte_round = ducks->at(i)->difficulte_round + round->roundCpt / 10;
        }
        looseByEscape = false;
        timer_escape->start(10000);
    }
}

void GraphicsView::attach_perdre(Game_over *looser)
{
    loose = looser;

    connect(loose, &Game_over::perdu, this,

            [this]() // fonction lambda
            {
                writed = true;
                this->showNormal();
                this->loose->hide();
                ammo->cptMunition = 3;
                score->scoreCpt = 0;
                score->nombreCanardTue = 0;
                round->roundCpt = 0;

                if (ducks->size() == 2)
                {
                    delete ducks->at(1);
                    ducks->removeAt(1);
                    delete ducks->at(0);
                    ducks->removeAt(0);
                }
                else if (ducks->size() == 1)
                {
                    delete ducks->at(0);
                    ducks->removeAt(0);
                }

                DuckCount = QRandomGenerator::global()->bounded(1, 3);
                //chien->nb_chien = DuckCount;

                for (int i = 0; i < DuckCount; i++)
                {
                    ducks->push_back(new Duck);

                    connect(ducks->back(), &Duck::canardVraimentMort, this, &GraphicsView::lesCanardsDoiventRespawn);

                    this->scene()->addItem(ducks->back());

                    pos_random = QRandomGenerator::global()->bounded(300, 900);
                    ducks->back()->setPos(pos_random, 570);

                    ducks->at(i)->difficulte_coin = difficulte;

                    ducks->at(i)->difficulte_round = ducks->at(i)->difficulte_round + round->roundCpt / 10;
                }
                looseByEscape = false;
                timer_escape->start(10000);
            });

    connect(loose, &Game_over::return_menu, this,

            [this]() // fonction lambda
            {
                this->loose->hide();
                this->level->showNormal();
                ammo->cptMunition = 3;
                looseByEscape = false;
                timer_escape->start(10000);
            });
}

//==================BOUM BOUM LE CANARD==================

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    // if (event->buttons() == Qt::LeftButton)
    // {
    //     for (int i = 0; i < DuckCount; i++)
    //     {
    //         if (((crosshair->coordinateMouse.rx()) >= ((ducks->at(i)->positionDuck.rx())) && ((crosshair->coordinateMouse.rx()) <= (ducks->at(i)->positionDuck.rx() + decalageLargeur))))
    //         {
    //             if (((crosshair->coordinateMouse.ry()) >= (ducks->at(i)->positionDuck.ry())) && ((crosshair->coordinateMouse.ry()) <= (ducks->at(i)->positionDuck.ry() + decalageHauteur)))
    //             {
    //                 if (ducks->at(i)->cliqueDessus == !compare)
    //                 {
    //                     ducks->at(i)->isDead = compare;
    //                     ducks->at(i)->cliqueDessus = compare;
    //                     (score->nombreCanardTue)++;
    //                     score->scoreCpt = score->nombreCanardTue * 1;
    //                     round->roundCpt = score->nombreCanardTue / 10;
    //                 }
    //             }
    //         }
    //     }
    //     (ammo->cptMunition)--;
    // }
}

//==================BOUM BOUM LE CANARD==================

void GraphicsView::timerEvent(QTimerEvent *event)
{
    // static int cpt_test = 0;

    // if (ecran->m_serial->isOpen())
    // {
    //     //crosshair->setPos(QPointF(crosshair->pos_x + 640, crosshair->pos_y + 384));

    //     if (crosshair->fireInTheHole == 1)
    //     {
    //         cpt_test++;
    //         for (int i = 0; i < DuckCount; i++)
    //         {
    //             if (((crosshair->pos_x) >= ((ducks->at(i)->positionDuck.rx()-640)) && ((crosshair->pos_x) <= (ducks->at(i)->positionDuck.rx()-640 + decalageLargeur))))
    //             {
    //                 if (((crosshair->pos_y) >= (ducks->at(i)->positionDuck.ry()-384)) && ((crosshair->pos_y) <= (ducks->at(i)->positionDuck.ry()-384 + decalageHauteur)))
    //                 {
    //                     if (ducks->at(i)->cliqueDessus == !compare)
    //                     {
    //                         ducks->at(i)->isDead = compare;
    //                         ducks->at(i)->cliqueDessus = compare;
    //                         (score->nombreCanardTue)++;
    //                         score->scoreCpt = score->nombreCanardTue * 1;
    //                         round->roundCpt = score->nombreCanardTue / 10;
    //                     }
    //                 }
    //             }
    //         }
    //         (ammo->cptMunition)--;
    //     }
    // }

    if ((ammo->cptMunition <= 0) && (ducks->size() >= 1) && (ducks->at(0)->isDead == !compare) && (ducks->at(0)->isDead2 == !compare) && (ducks->at(0)->vraimentMort == !compare))
    {

        if (writed)
        {
            pseudonyme = pseudo.toStdString().c_str();

            if (!fs::exists(path / "MVPs.json"))
            {
                std::ofstream ofs(path / "MVPs.json");
                nlohmann::json j1;

                j1["Pseudo"] = "None";
                j1["Score"] = 0;
                j1["Round"] = 0;

                j1["Pseudo2"] = "None";
                j1["Score2"] = 0;
                j1["Round2"] = 0;

                j1["Pseudo3"] = "None";
                j1["Score3"] = 0;
                j1["Round3"] = 0;
                ofs << j1;
                ofs.close();
            }

            std::ifstream ifs(path / "MVPs.json");

            nlohmann::json j2;

            j2 << ifs;

            if (score->scoreCpt > j2["Score"])
            {
                j2["Pseudo2"] = j2["Pseudo"];
                j2["Score2"] = j2["Score"];
                j2["Round2"] = j2["Round"];

                j2["Pseudo"] = pseudonyme;
                j2["Score"] = score->scoreCpt;
                j2["Round"] = round->roundCpt;
            }
            else if (score->scoreCpt > j2["Score2"])
            {
                j2["Pseudo3"] = j2["Pseudo2"];
                j2["Score3"] = j2["Score2"];
                j2["Round3"] = j2["Round2"];

                j2["Pseudo2"] = pseudonyme;
                j2["Score2"] = score->scoreCpt;
                j2["Round2"] = round->roundCpt;
            }
            else if (score->scoreCpt > j2["Score3"])
            {
                j2["Pseudo3"] = pseudonyme;
                j2["Score3"] = score->scoreCpt;
                j2["Round3"] = round->roundCpt;
            }

            loose->player_best->setText(QString::fromStdString(j2["Pseudo"]));
            loose->player_best_deuxieme->setText(QString::fromStdString(j2["Pseudo2"]));
            loose->player_best_troisieme->setText(QString::fromStdString(j2["Pseudo3"]));

            int test = j2["Score"];
            int test2 = j2["Score2"];
            int test3 = j2["Score3"];

            loose->player_best_scorus->setText(QString::number(test));
            loose->player_best_deuxieme_scorus->setText(QString::number(test2));
            loose->player_best_troisieme_scorus->setText(QString::number(test3));

            ifs.close();

            std::ofstream ofs(path / "MVPs.json");

            ofs << std::setw(4) << j2 << std::endl;

            ofs.close();

            writed = false;
        }

        loose->show();
        this->hide();
        urss_miam.stop();
        momo_sound.stop();
    }
    //label_movie.setPos(500,500);
    // label_movie.setMovie(movie);
    // movie->start();
}

bool GraphicsView::viewportEvent(QEvent *event)
{

    return QGraphicsView::viewportEvent(event);
}
 