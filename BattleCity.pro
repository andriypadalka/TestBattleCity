#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T23:03:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleCity
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    workspace.cpp \
    BaseObstacle.cpp \
    tank.cpp \
    levelone.cpp \
    dlgsettings.cpp \
    streetwidthshow.cpp \
    settings.cpp \
    shell.cpp

HEADERS  += mainwindow.h \
    workspace.h \
    BaseObstacle.h \
    Includes.h \
    tank.h \
    baselevel.h \
    levelone.h \
    dlgsettings.h \
    settings.h \
    streetwidthshow.h \
    Enums.h \
    shell.h \
    baseobstcontainer.h \
    ObstContainer.hpp

FORMS    += mainwindow.ui \
    dlgsettings.ui

OTHER_FILES += \
    Tasks.txt \
    References.txt
