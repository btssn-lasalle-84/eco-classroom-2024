QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    basededonnees.cpp \    
    ihmecoclassroom.cpp \
    salleeco.cpp

HEADERS += \
    basededonnees.h \
    ihmecoclassroom.h \
    indices.h \
    mesures.h \
    etats.h \
    salleeco.h

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
