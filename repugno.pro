#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T04:21:10
#
#-------------------------------------------------

QT       += core widgets network gui



TARGET = repugno
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp repugnoapplication.cpp \
    repugnotray.cpp \
    dummyobject.cpp \
    i2plauncher.cpp

HEADERS += repugnoapplication.h \
    repugnotray.h \
    dummyobject.h \
    i2plauncher.h

RESOURCES += \
    resources.qrc
