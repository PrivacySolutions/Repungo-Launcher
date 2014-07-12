#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T04:21:10
#
#-------------------------------------------------

QT       += core widgets gui



TARGET = Repugno

# Use the console config only for debugging. Disable it at release

CONFIG -= console
CONFIG   -= app_bundle

TEMPLATE = app

win32:RC_FILE = win32res.rc


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
