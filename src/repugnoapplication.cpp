#include "repugnoapplication.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <stdio.h> // printf
#include <stdlib.h> // getenv
#include <QProcess>
#include <QThread>

#include "versioninfo.h"

#include "utils.h"

#include <QMessageBox>

#include "i2plauncher.h"
#include "childprocessthread.h"


#ifdef BUILD_WITH_BROWSER
QString RepugnoApplication::getBrowserParameters(QString concat, bool init)
{
    // Firefox startup
#ifdef DEBUG
    QString parameters = "-jsconsole ";
#else
    QString parameters = "--args ";
#endif
    if (init)
    {
#ifdef WIN32
        parameters += QString("-profile \"") + RepugnoApplication::applicationDirPath()+QDir::separator()+"Config\\Browser\\profile.default\" ";
#else
        parameters += QString("-profile \"") + RepugnoApplication::applicationDirPath()+QDir::separator()+"Config/Browser/profile.default\" ";
#endif
        parameters += "  -no-remote "+concat;
    }
    else
    {
        parameters += " -new-tab "+concat;
    }

    return parameters;
}

void RepugnoApplication::LaunchBrowser()
{
    QString temp(m_abscondPath+RepugnoApplication::getBrowserParameters(QString("-new-window http://127.0.0.1:7070"), true));
    qDebug() << "Trying to launch " << temp;
    AppLauncher *al = new AppLauncher(temp);
    ChildProcessThread *cpt = new ChildProcessThread(NULL, al, false);
    cpt->start();
}
#endif

void RepugnoApplication::tellAboutTheFuckup(QString title, QString msg)
{
    QMessageBox tmpBox;
    tmpBox.setIcon(QMessageBox::Critical);
    tmpBox.setWindowTitle(title);
    tmpBox.setText(msg+
      QString("\n\nIf you feel need to ask for help to fix this, please use the #Abscond channel on either I2P, Freenode or Greyhat. A relay bot connect the networks together, so it won't have anything to say where you join."));
    tmpBox.exec();
}

void RepugnoApplication::rememberLastNight()
{
    // Load config
    QString settingsFile = RepugnoApplication::applicationDirPath()+QDir::separator()+"Config"+QDir::separator()+"RepugnoAppSettings.conf";
    QFile tmp(settingsFile);
    qDebug() << "Settings file: %s", qPrintable(settingsFile);
    QSettings m_longtermMemory(settingsFile, QSettings::IniFormat); // Use ini format because of support for multiple OS
    if (!tmp.exists())
    {
        qDebug() << "Settings file not found. Creating one!";
        configReset();
    }

    qDebug() << "Trying to load paths";
    // Preload paths
    locateI2P();
#ifdef BUILD_WITH_BROWSER
    locateAbscond();
#endif

    // Start with I2P, it needs 2minutes.
    qDebug() << "I2P Path is: " << m_i2pPath;
    I2PLauncher *i2pLauncher = new I2PLauncher(m_i2pPath);
    ChildProcessThread *cpt = new ChildProcessThread(NULL, i2pLauncher, false);
    cpt->start();

    // Verifying tha i2pd is runnig
    const char *ipaddr = "127.0.0.1";
    int port = 7070;
    int maxTries = 30;
    int tries;
    bool error = false;
    while (!is_alive(ipaddr, port, 1 /* Testing 1sec for each round */))
    {
        // Waiting... :)
        if (tries==maxTries)
        {
            qDebug() << "Trying to connect to i2pd...";
            error = true;
        }
        tries++;
    }
    if (error)
    {
        tellAboutTheFuckup(QString("I2P isn't responding. Errno #0001"),QString("I2P doesn't respond. The timeout has reached. Something must be wrong!"));
        QCoreApplication::exit(1);
    }

#ifdef BUILD_WITH_BROWSER
    // Browser
    LaunchBrowser();
#endif
}

#ifdef BUILD_WITH_BROWSER
void RepugnoApplication::locateAbscond()
{
#ifdef Q_OS_MACX
    // On OSX, if correct installed, we will be in the .app bundle now, and firefox will be next to us.
    QDir browserDir(QCoreApplication::applicationDirPath());
#else
    QDir browserDir(QCoreApplication::applicationDirPath()+QDir::separator()+"Browser");
#endif
    if (!browserDir.exists())
    {
        QString t = "Critical error! Can't find the browser!!";
        qDebug() << t;
        tellAboutTheFuckup(QString("Critical error! Errno #0002"), t);
        QCoreApplication::exit(1);
    }
#ifdef WIN32
    QFile browserFile(browserDir.absolutePath()+QDir::separator()+"firefox.exe");
#else
    QFile browserFile(browserDir.absolutePath()+QDir::separator()+"firefox");
#endif
    if (!browserFile.exists())
    {
        QString t = "Critical error! Can't find the browser!! found the folder but not the browser executable!";
        qDebug() << t;
        tellAboutTheFuckup(QString("Critical error! Errno #0003"), t);
        QCoreApplication::exit(1);
    }
    qDebug() << "Browser path found at " << browserDir.absolutePath();
    QFileInfo fi(browserFile);
    // Adding space at last, won't effect commands and will prevent parameter mistakes.
    m_abscondPath = fi.absoluteFilePath()+QString(" ");
}
#endif

void RepugnoApplication::locateI2P()
{
    QDir i2pDir(QCoreApplication::applicationDirPath()+"/i2pd");

    if (!i2pDir.exists())
    {
        QString t = "Critical error! Can't find I2P!!";
        qDebug() << t;
        tellAboutTheFuckup(QString("Critical error! Errno #0008"), t);
        QCoreApplication::exit(1);
    }
    qDebug() << "Found I2P path!";
    m_i2pPath = i2pDir.absolutePath();
}

void RepugnoApplication::configReset()
{

}

void RepugnoApplication::createTrayIcon()
{
    RepugnoTray m_trayIcon();
}


QString RepugnoApplication::getI2PPath()
{
    return m_i2pPath;
}

#ifdef BUILD_WITH_BROWSER
QString RepugnoApplication::getBrowserPath()
{
    QFileInfo path(m_abscondPath);
    return path.canonicalPath();
}
#endif

void RepugnoApplication::becomeSelfaware()
{
    qDebug() << "Starting up Repungo launcher!";
    qDebug() << "Starting with becomming selfaware.";
    // Setting application information
    setApplicationName("Repungo Launcher (Abscond application)");
    //setApplicationDisplayName("The Abscond browser bundle");
    setApplicationVersion(version);
    setOrganizationDomain("privacysolutions.no");
    setOrganizationName("The Privacy solutions project");
    setQuitOnLastWindowClosed(false);
#ifndef WIN32
    setenv("REPUGNO_LAUNCHER", version, 1);
#endif

}


RepugnoApplication::RepugnoApplication(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    becomeSelfaware();
    createTrayIcon();
    rememberLastNight();
}
