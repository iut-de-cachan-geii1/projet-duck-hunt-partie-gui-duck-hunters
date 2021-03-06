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

#include "score.h"
#include <QFont>

Score::Score()
    : scoreCpt(0.0),
      nombreCanardTue(0),
      label(new QLabel)
{
}

QRectF Score::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath Score::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 75, 71);
    return path;
}

void Score::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font();
    const QRect rectangle = QRect(0, 0, 400, 50);
    QRect boundingRect;
    font.setPixelSize(38);
    painter->setFont(font);
    //painter->drawText(QPointF(0, 0), QString("Score = ") + QString::number(scoreCpt));
    painter->drawText(rectangle, 0, QString("score = ") + QString::number(scoreCpt), &boundingRect);

    QPen pen = painter->pen();
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawRect(boundingRect.adjusted(0, 0, -pen.width(), -pen.width()));
}
