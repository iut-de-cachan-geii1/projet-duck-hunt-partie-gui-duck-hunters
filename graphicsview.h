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

#pragma once
#include <QGraphicsView>
#include "crosshair.h"
#include "duck.h"
#include "munition.h"
#include "score.h"
#include "ecran_acceuil.h"
#include "chien.h"
#include "round.h"
#include "choix_level.h"
#include "game_over.h"
#include <fstream>
#include <string>
#include <iostream>

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::fstream;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QGraphicsScene *scene = nullptr, QWidget *parent = nullptr);

//=============Fonction attache================================

    void attachCrosshair(Crosshair *parametreCrosshair);
    void attachDucks(QList<Duck*> * DucksQuiFautAttacher);
    void attachAmmo(Munition *munitionQuiFautAttacher);
    void attachScore(Score *scoreQuiFautAttacher);
    void attachChien(Chien *chienQuiFautAttacher);
    //void attachChien(Chien *chienQuiFautAttacher);
    void attachRound(Round *roundQuiFautAttacher);

//=============Fonction attache fin===========================

    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    bool viewportEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void attach_ecran_acceuil(ecran_acceuil*ecran);
    void attach_choix_level(choix_level* level);
    void attach_perdre(Game_over* looser);
    void lesCanardsSontMorts(Duck* canardRecu);


    int DuckCount;
    bool respawn = false;
    bool has_pseudo;

    
private:
    qreal totalScaleFactor = 1;
    Crosshair* crosshair;
    QList<Duck*> *ducks;
    Munition *ammo;
    Score *score;
    Chien *chien;
    Round *round;
    int pos_random;
    bool compare;
    ecran_acceuil*ecran;
    choix_level* level;
    int maps;
    int levels;
    QString pseudo;
    Game_over* loose;
    bool vraiment_perdu;
    float difficulte;
    Duck* veryDead;

signals:
// void ilFautFaireRespawnLesCanards();

public slots:
void lesCanardsDoiventRespawn(Duck* canardATuer);

};
