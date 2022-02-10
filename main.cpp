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

#include <QGraphicsVideoItem>
#include <QRandomGenerator>
#include <QApplication>
#include <cmath>
#include <QPainterPath>
#include <QMediaPlayer>
#include <QList>

static constexpr int DuckCount = 2;
QList<Duck *> listDuck;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1280, 769);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Duck *duck = new Duck;
    listDuck.emplaceBack(duck);

    Crosshair *crosshair = new Crosshair;
    static int pos_random = QRandomGenerator::global()->bounded(200, 900);
    duck->setPos(pos_random, 570);
    crosshair->setPos(640, 384);
    scene.addItem(listDuck.at(0));
    scene.addItem(crosshair);
    // scene.addRect(0,0,1201,600);

    GraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    // Creation des
    view.setBackgroundBrush(QPixmap(":/images/background.png"));
    view.setForegroundBrush(QPixmap(":/images/foreground.png"));

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::QGraphicsView::FullViewportUpdate);

    view.attachDucks(listDuck);
    view.attachCrosshair(crosshair);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Duck hunt"));

    view.showNormal();
    return QApplication::exec();
}
