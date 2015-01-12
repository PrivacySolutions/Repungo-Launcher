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

win32:RC_FILE = res/win32res.rc
win32:LIBS = -lwsock32 -lws2_32

SOURCES += src/main.cpp src/repugnoapplication.cpp \
    src/repugnotray.cpp \
    src/i2plauncher.cpp \
    src/applauncher.cpp \
    src/childprocessthread.cpp \
    src/utils.cpp

HEADERS += src/repugnoapplication.h \
    src/repugnotray.h \
    src/i2plauncher.h \
    src/applauncher.h \
    src/childprocessthread.h \
    src/versioninfo.h \
    src/utils.h \
    build.h

RESOURCES += \
    src/resources.qrc
