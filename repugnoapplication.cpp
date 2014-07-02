#include "repugnoapplication.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <stdio.h> // printf
#include <stdlib.h> // getenv
#include <QProcess>

#include <QMessageBox>

#include "i2plauncher.h"


void RepugnoApplication::InitAll()
{
    // Start with I2P, it needs 2minutes.
    I2PLauncher *i2pLauncher = new I2PLauncher(jrePath, i2pPath);
    i2pLauncher->Run();

    // Message about 2min warmup
    if (longtermMemory->value("donotshowagainboxes/thewarmupinfo", 0).toInt() == 0)
    {
        QMessageBox msgBox;
        longtermMemory->setValue("donotshowagainboxes/thewarmupinfo", 1);
        msgBox.setText(tr("Hi and welcome!\n\nPlease take those 30 seconds it takes to read this; like Tor isn't, I2P is 100% decentralizated."
                       "\nThis means that it usually takes 2-3minutes before you can start using I2P as regular.\n\n"
                       "Please also note that the router itself is self-learning which means that the longer you keep it running,"
                       "\nprobably the better speed you get too!\n\nEnjoy!"));
        msgBox.exec();
    }

    // Firefox startup
#ifdef WIN32
#ifdef DEBUG
    QString parameters = "-jsconsole -no-remote -profile \""+
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config\\Browser\\profile.default\"";
#else
    QString parameters = "--args -no-remote -profile \""+
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config\\Browser\\profile.default\"";
#endif
#else
#ifdef DEBUG
    QString parameters = "-jsconsole -no-remote -profile \""+
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config/Browser/profile.default\"";
#else
    QString parameters = "--args -no-remote -profile \""+
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config/Browser/profile.default\"";
#endif
#endif
    QString *temp = new QString(RepugnoApplication::applicationDirPath()+QDir::separator()+"firefox "+parameters);
    AppLauncher *al = new AppLauncher(temp);
    delete temp;
}

void RepugnoApplication::rememberLastNight()
{
    // Load config
    QString settingsFile = RepugnoApplication::applicationDirPath()+QDir::separator()+"RepugnoAppSettings.conf";
    QFile *tmp = new QFile(settingsFile);
    qDebug() << "Settings file: %s", qPrintable(settingsFile);
    longtermMemory = new QSettings(settingsFile, QSettings::IniFormat); // Use ini format because of support for multiple OS
    if (!tmp->exists())
    {
        qDebug() << "Settings file not found. Creating one!";
        configReset();
    }

    qDebug() << "Trying to load paths";
    // Preload paths
    locateJRE();
    locateI2P();
    //locateAbscond();

    // Init process
    InitAll();
}

void RepugnoApplication::locateAbscond()
{
#ifdef Q_OS_MACX
    // On OSX, if correct installed, we will be in the .app bundle now, and firefox will be next to us.
    QDir *browserDir = new QDir(QCoreApplication::applicationDirPath());
#else
    QDir *browserDir = new QDir(QCoreApplication::applicationDirPath()+QDir::separator()+"Browser");
#endif
    if (!browserDir->exists())
    {
        qDebug() << "Critical error! Can't find the browser!!";
        QCoreApplication::exit(1);
    }
#ifdef Q_OS_MACX
    QFile *browserFile = new QFile(browserDir->absolutePath()+QDir::separator()+"firefox");
#elif WIN32 // Windows requires .exe as always.
    QFile *browserFile = new QFile(browserDir->absolutePath()+QDir::separator()+"firefox.exe");
#else
    QFile *browserFile = new QFile(browserDir->absolutePath()+QDir::separator()+"firefox");
#endif
    if (!browserFile->exists())
    {
        qDebug() << "Critical error! Can't find the browser!! found the folder but not the browser executable!";
        QCoreApplication::exit(1);
    }
    qDebug() << "Browser path found at " << browserDir->absolutePath();
    QFileInfo fi(*browserFile);
    delete browserFile;
    delete browserDir;
    abscondPath = fi.absoluteFilePath();
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
            qDebug() << "Critical error! Can't find the JRE or environment variable JAVA_HOME!!!";
            QCoreApplication::exit(1);
        }
        // JAVA_HOME was set. Dircheck
        QDir *jh2 = new QDir(jh);
        if (!jh2->exists())
        {
            // JAVA_HOME is not correct, Can't run I2P.. Run and hide! No one can save you!
            qDebug() << "Critical error! The JAVA_HOME environment variable seems misconfigured!!";
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
    QFile *javaExecFile = new QFile(jreDir + QDir::separator() + javaExec);
    if (!javaExecFile->exists())
    {
        // The java binary is not correct, Can't run I2P.. Run and hide! No one can save you!
        qDebug() << "Critical error! The JAVA_HOME environment variable seems misconfigured!!";
        QCoreApplication::exit(1);
    }
    qDebug() << "Found the JRE!";
    // Setting the JRE path
    jrePath = jreDir;
}

void RepugnoApplication::locateI2P()
{
    QDir *i2pDir = new QDir(QCoreApplication::applicationDirPath()+QDir::separator()+"i2p");
    if (!i2pDir->exists())
    {
        qDebug() << "Critical error! Can't find I2P!!";
        QCoreApplication::exit(1);
    }
    qDebug() << "Found I2P path!";
    i2pPath = i2pDir->absolutePath();
}

void RepugnoApplication::configReset()
{

}

void RepugnoApplication::createTrayIcon()
{
    trayIcon = new RepugnoTray();
}

QString RepugnoApplication::getJREPath()
{
    return jrePath;
}

QString RepugnoApplication::getI2PPath()
{
    return i2pPath;
}

QString RepugnoApplication::getBrowserPath()
{
    return abscondPath;
}

void RepugnoApplication::becomeSelfaware()
{
    // TODO: Move somewhere else
    const char* version = "0.1";

    qDebug() << "Becomming selfaware.";
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
    rememberLastNight();
}
