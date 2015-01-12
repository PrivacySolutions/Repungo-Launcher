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

#DEFINES += BUILD_WITH_BROWSER=1

TEMPLATE = app

win32:RC_FILE = win32res.rc
win32:LIBS = -lwsock32 -lws2_32

SOURCES += main.cpp repugnoapplication.cpp \
    repugnotray.cpp \
    i2plauncher.cpp \
    applauncher.cpp \
    childprocessthread.cpp \
    utils.cpp

HEADERS += repugnoapplication.h \
    repugnotray.h \
    i2plauncher.h \
    applauncher.h \
    childprocessthread.h \
    versioninfo.h \
    utils.h

RESOURCES += \
    resources.qrc
