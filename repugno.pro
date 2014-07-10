#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T04:21:10
#
#-------------------------------------------------

QT       += core widgets network gui



TARGET = repugno
CONFIG += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp repugnoapplication.cpp \
    repugnotray.cpp \
    i2plauncher.cpp \
    dummyobject.cpp \
    applauncher.cpp \
    childprocessthread.cpp \
    ilauncher.cpp

HEADERS += repugnoapplication.h \
    repugnotray.h \
    i2plauncher.h \
    dummyobject.h \
    applauncher.h \
    childprocessthread.h \
    ilauncher.h

RESOURCES += \
    resources.qrc
