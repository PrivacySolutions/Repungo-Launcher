#include "repugnoapplication.h"
#include <QDir>
#include <stdio.h> // printf
#include <stdlib.h> // getenv




void RepugnoApplication::rememberLastNight()
{
    QString settingsFile = RepugnoApplication::applicationDirPath()+QDir::separator()+"RepugnoAppSettings.conf";
    QFile *tmp = new QFile(settingsFile);
    printf("Settings file: %s", qPrintable(settingsFile));
    longtermMemory = new QSettings(settingsFile, QSettings::IniFormat); // Use ini format because of support for multiple OS
    if (!tmp->exists())
    {
        printf("Settings file not found. Creating one!");
        configReset();
    }
    locateJRE();
    locateI2P();
    locateAbscond();
}

void RepugnoApplication::locateAbscond()
{
    QDir *i2pDir = new QDir(QCoreApplication::applicationDirPath()+QDir::separator()+"Browser");
    if (!i2pDir->exists())
    {
        printf("Critical error! Can't find the browser!!");
        QCoreApplication::exit(1);
    }
    i2pPath = i2pDir->absolutePath();
}

void RepugnoApplication::locateJRE()
{
    // Should be in the same folder.
    QString jreDir;
    QDir *javaHome = new QDir(QCoreApplication::applicationDirPath()+QDir::separator()+"jre");
    if (!javaHome->exists())
    {
        // OK... Not in the normal location. Let's check environment.
        char* jh = getenv("JAVA_HOME");
        if (jh==NULL)
        {
            // Java can't be found. We must exit hard.. Can't launch I2P....
            printf("Critical error! Can't find the JRE or environment variable JAVA_HOME!!!");
            QCoreApplication::exit(1);
        }
        // JAVA_HOME was set. Dircheck
        QDir *jh2 = new QDir(jh);
        if (!jh2->exists())
        {
            // JAVA_HOME is not correct, Can't run I2P.. Run and hide! No one can save you!
            printf("Critical error! The JAVA_HOME environment variable seems misconfigured!!");
            QCoreApplication::exit(1);
        }
        jreDir = jh;
    }
    jreDir = javaHome->absolutePath();
    // OK, it passed. Time for last check. The java executable
#ifdef WIN32
    QString javaExec = "bin\\java.exe";
#else
    QString javaExec = "bin/java";
#endif
    QFile *javaExecFile = new QFile(javaExec);
    if (!javaExecFile->exists())
    {
        // The java binary is not correct, Can't run I2P.. Run and hide! No one can save you!
        printf("Critical error! The JAVA_HOME environment variable seems misconfigured!!");
        QCoreApplication::exit(1);
    }
    // Setting the JRE path
    jrePath = jreDir;
}

void RepugnoApplication::locateI2P()
{
    QDir *i2pDir = new QDir(QCoreApplication::applicationDirPath()+QDir::separator()+"i2p");
    if (!i2pDir->exists())
    {
        printf("Critical error! Can't find I2P!!");
        QCoreApplication::exit(1);
    }
    i2pPath = i2pDir->absolutePath();
}

void RepugnoApplication::configReset()
{

}

void RepugnoApplication::createTrayIcon()
{
    trayIcon = new RepugnoTray();
}



void RepugnoApplication::becomeSelfaware()
{
    // TODO: Move somewhere else
    const char* version = "0.1";

    // Setting application information
    setApplicationName("Repungo Launcher");
    //setApplicationDisplayName("The Abscond bundle");
    setApplicationVersion(version);
    setOrganizationDomain("sigterm.no");
    setOrganizationName("Sigterm");
    setQuitOnLastWindowClosed(false);
#ifndef WIN32
    setenv("REPUGNO_LAUNCHER", version, 1);
#else
    /* WTF too much code. Find a better way than SetEnvironmentVariable from kernel32
    #include <windows.h>
    HMODULE kDLL = LoadLibraryA("kernel32.dll");
    if (!kDLL)
    {
        qDebug << "Failed to load library kernel32";
    }*/
#endif

}


RepugnoApplication::RepugnoApplication(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    becomeSelfaware();
    createTrayIcon();
}
