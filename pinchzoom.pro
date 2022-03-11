QT += widgets multimedia multimediawidgets serialport

HEADERS += \
        choix_level.h \
        crosshair.h \
        duck.h \
        ecran_acceuil.h \
        game_over.h \
        graphicsview.h \
        menu.h \
        mouse.h \
        munition.h \
        round.h \
        score.h
SOURCES += \
    choix_level.cpp \
    crosshair.cpp \
    duck.cpp \
    ecran_acceuil.cpp \
    game_over.cpp \
	main.cpp \
        graphicsview.cpp \
    menu.cpp \
    munition.cpp \
    round.cpp \
    score.cpp

RESOURCES += \
	mice.qrc

FORMS += \
    choix_level.ui \
    ecran_acceuil.ui \
    game_over.ui

