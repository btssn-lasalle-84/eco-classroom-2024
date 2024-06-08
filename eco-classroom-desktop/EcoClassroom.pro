QT += core gui widgets sql
QT += mqtt


CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    dialoguemqtt.cpp \
    main.cpp \
    basededonnees.cpp \    
    ihmecoclassroom.cpp \
    salleeco.cpp

HEADERS += \
    basededonnees.h \
    dialoguemqtt.h \
    ihmecoclassroom.h \
    indices.h \
    mesures.h \
    etats.h \
    salleeco.h

RESOURCES += eco-classroom-desktop.qrc

DISTFILES += \
    eco-classroom-desktop.qss \
    arrow-down.png

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
