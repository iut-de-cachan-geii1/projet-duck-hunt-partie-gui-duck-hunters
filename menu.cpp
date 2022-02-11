// /****************************************************************************
// **
// ** Copyright (C) 2016 The Qt Company Ltd.
// ** Contact: https://www.qt.io/licensing/
// **
// ** This file is part of the examples of the Qt Toolkit.
// **
// ** $QT_BEGIN_LICENSE:BSD$
// ** Commercial License Usage
// ** Licensees holding valid commercial Qt licenses may use this file in
// ** accordance with the commercial license agreement provided with the
// ** Software or, alternatively, in accordance with the terms contained in
// ** a written agreement between you and The Qt Company. For licensing terms
// ** and conditions see https://www.qt.io/terms-conditions. For further
// ** information use the contact form at https://www.qt.io/contact-us.
// **
// ** BSD License Usage
// ** Alternatively, you may use this file under the terms of the BSD license
// ** as follows:
// **
// ** "Redistribution and use in source and binary forms, with or without
// ** modification, are permitted provided that the following conditions are
// ** met:
// **   * Redistributions of source code must retain the above copyright
// **     notice, this list of conditions and the following disclaimer.
// **   * Redistributions in binary form must reproduce the above copyright
// **     notice, this list of conditions and the following disclaimer in
// **     the documentation and/or other materials provided with the
// **     distribution.
// **   * Neither the name of The Qt Company Ltd nor the names of its
// **     contributors may be used to endorse or promote products derived
// **     from this software without specific prior written permission.
// **
// **
// ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
// **
// ** $QT_END_LICENSE$
// **
// ****************************************************************************/

// #include "menu.h"

// #include <QGraphicsScene>
// #include <QPainter>
// #include <QRandomGenerator>
// #include <QStyleOption>
// #include <qmath.h>
// #include <QMovie>
// #include <QLabel>
// #include <QDialog>
// #include <QPixmap>



// MainMenu::MainMenu(std::shared_ptr<Context> &context)
//     : m_context(context), m_isPlayButtonSelected(true),
//       m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
//       m_isExitButtonPressed(false)
// {
// }

// MainMenu::~MainMenu()
// {
// }

// void MainMenu::Init()
// {
//     m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");

//     // Title
//     m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
//     m_gameTitle.setString("Snake Game");
//     m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
//                           m_gameTitle.getLocalBounds().height / 2);
//     m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
//                             m_context->m_window->getSize().y / 2 - 150.f);

//     // Play Button
//     m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
//     m_playButton.setString("Play");
//     m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
//                            m_playButton.getLocalBounds().height / 2);
//     m_playButton.setPosition(m_context->m_window->getSize().x / 2,
//                              m_context->m_window->getSize().y / 2 - 25.f);
//     m_playButton.setCharacterSize(20);

//     // Exit Button
//     m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
//     m_exitButton.setString("Exit");
//     m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
//                            m_exitButton.getLocalBounds().height / 2);
//     m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
//                              m_context->m_window->getSize().y / 2 + 25.f);
//     m_exitButton.setCharacterSize(20);
// }

// void MainMenu::ProcessInput()
// {
//     sf::Event event;
//     while (m_context->m_window->pollEvent(event))
//     {
//         if (event.type == sf::Event::Closed)
//         {
//             m_context->m_window->close();
//         }
//         else if (event.type == sf::Event::KeyPressed)
//         {
//             switch (event.key.code)
//             {
//             case sf::Keyboard::Up:
//             {
//                 if (!m_isPlayButtonSelected)
//                 {
//                     m_isPlayButtonSelected = true;
//                     m_isExitButtonSelected = false;
//                 }
//                 break;
//             }
//             case sf::Keyboard::Down:
//             {
//                 if (!m_isExitButtonSelected)
//                 {
//                     m_isPlayButtonSelected = false;
//                     m_isExitButtonSelected = true;
//                 }
//                 break;
//             }
//             case sf::Keyboard::Return:
//             {
//                 m_isPlayButtonPressed = false;
//                 m_isExitButtonPressed = false;

//                 if (m_isPlayButtonSelected)
//                 {
//                     m_isPlayButtonPressed = true;
//                 }
//                 else
//                 {
//                     m_isExitButtonPressed = true;
//                 }

//                 break;
//             }
//             default:
//             {
//                 break;
//             }
//             }
//         }
//     }
// }

// void MainMenu::Update(sf::Time deltaTime)
// {
//     if(m_isPlayButtonSelected)
//     {
//         m_playButton.setFillColor(sf::Color::Black);
//         m_exitButton.setFillColor(sf::Color::White);
//     }
//     else
//     {
//         m_exitButton.setFillColor(sf::Color::Black);
//         m_playButton.setFillColor(sf::Color::White);
//     }
    
//     if(m_isPlayButtonPressed)
//     {
//         m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
//     }
//     else if(m_isExitButtonPressed)
//     {
//         m_context->m_window->close();
//     }
    
// }

// void MainMenu::Draw()
// {
//     m_context->m_window->clear(sf::Color::Blue);
//     m_context->m_window->draw(m_gameTitle);
//     m_context->m_window->draw(m_playButton);
//     m_context->m_window->draw(m_exitButton);
//     m_context->m_window->display();
// }
