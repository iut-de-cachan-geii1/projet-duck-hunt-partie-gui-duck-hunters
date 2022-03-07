QT += widgets multimedia multimediawidgets serialport

HEADERS += \
        choix_level.h \
        crosshair.h \
        duck.h \
        ecran_acceuil.h \
        game_over.h \
        graphicsview.h \
        menu.h \
        mouse.h
SOURCES += \
    choix_level.cpp \
    crosshair.cpp \
    duck.cpp \
    ecran_acceuil.cpp \
    game_over.cpp \
	main.cpp \
        graphicsview.cpp \
    menu.cpp

RESOURCES += \
	mice.qrc

FORMS += \
    choix_level.ui \
    ecran_acceuil.ui \
    game_over.ui

