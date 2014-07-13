#include "repugnoapplication.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <stdio.h> // printf
#include <stdlib.h> // getenv
#include <QProcess>
#include <QThread>

#include <QMessageBox>

#include "i2plauncher.h"
#include "childprocessthread.h"

QString RepugnoApplication::getBrowserParameters()
{
    // Firefox startup
#ifdef WIN32
#ifdef DEBUG
    QString parameters = "-jsconsole -no-remote -profile \""+
#else
    QString parameters = "--args -no-remote -profile \""+
#endif
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config\\Browser\\profile.default\" -new-window http://127.0.0.1:7657 ";
#else
#ifdef DEBUG
    QString parameters = "-jsconsole -no-remote -profile \""+
#else
    QString parameters = "--args -no-remote -profile \""+
#endif
            RepugnoApplication::applicationDirPath()+QDir::separator()+"Config/Browser/profile.default\" -new-window http://127.0.0.1:7657 ";
#endif
    return parameters;
}

void RepugnoApplication::LaunchBrowser()
{
    QString temp(m_abscondPath+RepugnoApplication::getBrowserParameters());
    qDebug() << "Trying to launch " << m_abscondPath+RepugnoApplication::getBrowserParameters();
    AppLauncher *al = new AppLauncher(temp);
    ChildProcessThread *cpt = new ChildProcessThread(NULL, al, false);
    cpt->start();
}

void RepugnoApplication::InitAll()
{
    // Start with I2P, it needs 2minutes.
    qDebug() << "JRE Path is: " << m_jrePath;
    qDebug() << "I2P Path is: " << m_i2pPath;
    I2PLauncher *i2pLauncher = new I2PLauncher(m_jrePath, m_i2pPath);
    ChildProcessThread *cpt = new ChildProcessThread(NULL, i2pLauncher, false);
    cpt->start();

    // Message about 2min warmup
    if (m_longtermMemory->value("donotshowagainboxes/thewarmupinfo", 0).toInt() == 0)
    {
        QMessageBox msgBox;
        m_longtermMemory->setValue("donotshowagainboxes/thewarmupinfo", 1);
        msgBox.setText(tr("Hi and welcome!\n\nPlease take those 30 seconds it takes to read this; like Tor isn't, I2P is 100% decentralizated."
                       "\nThis means that it usually takes 2-3minutes before you can start using I2P as regular.\n\n"
                       "Please also note that the router itself is self-learning which means that the longer you keep it running,"
                       "\nprobably the better speed you get too!\n\nEnjoy!"));
        msgBox.exec();
    }

    // Give it 10sec to launch I2P
    QMessageBox msgBox;
    msgBox.setText(tr("Please give me 10sec while the JRE loads I2P before I launch the router console for you!"));
    msgBox.exec();
//    QThread::sleep(10);
    sleep(10);

    // Browser
    LaunchBrowser();
}

void RepugnoApplication::rememberLastNight()
{
    // Load config
    QString settingsFile = RepugnoApplication::applicationDirPath()+QDir::separator()+"Config"+QDir::separator()+"RepugnoAppSettings.conf";
    QFile tmp(settingsFile);
    qDebug() << "Settings file: %s", qPrintable(settingsFile);
    m_longtermMemory = new QSettings(settingsFile, QSettings::IniFormat); // Use ini format because of support for multiple OS
    if (!tmp.exists())
    {
        qDebug() << "Settings file not found. Creating one!";
        configReset();
    }

    qDebug() << "Trying to load paths";
    // Preload paths
    locateJRE();
    locateI2P();
    locateAbscond();

    // Init process
    InitAll();
}

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
        qDebug() << "Critical error! Can't find the browser!!";
        QCoreApplication::exit(1);
    }
#ifdef WIN32
    QFile browserFile(browserDir.absolutePath()+QDir::separator()+"firefox.exe");
#else
    QFile browserFile(browserDir.absolutePath()+QDir::separator()+"firefox");
#endif
    if (!browserFile.exists())
    {
        qDebug() << "Critical error! Can't find the browser!! found the folder but not the browser executable!";
        QCoreApplication::exit(1);
    }
    qDebug() << "Browser path found at " << browserDir.absolutePath();
    QFileInfo fi(browserFile);
    // Adding space at last, won't effect commands and will prevent parameter mistakes.
    m_abscondPath = fi.absoluteFilePath()+QString(" ");
}

void RepugnoApplication::locateJRE()
{
    // Should be in the same folder.
    QString jreDir;
    QDir javaHome(QCoreApplication::applicationDirPath()+QDir::separator()+"I2P"+QDir::separator()+"jre");
    if (!javaHome.exists())
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
        QDir jh2(jh);
        if (!jh2.exists())
        {
            // JAVA_HOME is not correct, Can't run I2P.. Run and hide! No one can save you!
            qDebug() << "Critical error! The JAVA_HOME environment variable seems misconfigured!!";
            QCoreApplication::exit(1);
        }
        jreDir = jh;
    }
    jreDir = javaHome.absolutePath();
    // OK, it passed. Time for last check. The java executable

    // WIN32 NOTE: In this case exe is required since it's a file check.
#ifdef WIN32
    QString javaExec = "bin\\java.exe";
#else
    QString javaExec = "bin/java";
#endif
    QFile javaExecFile(jreDir + QDir::separator() + javaExec);
    if (!javaExecFile.exists())
    {
        // The java binary is not correct, Can't run I2P.. Run and hide! No one can save you!
        qDebug() << "Critical error! The JAVA_HOME environment variable seems misconfigured!!";
        QCoreApplication::exit(1);
    }
    qDebug() << "Found the JRE!";
    // Setting the JRE path
    m_jrePath = jreDir;
}

void RepugnoApplication::locateI2P()
{
    QDir i2pDir(QCoreApplication::applicationDirPath()+QDir::separator()+"I2P"+QDir::separator()+"I2PApp");
    if (!i2pDir.exists())
    {
        qDebug() << "Critical error! Can't find I2P!!";
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
    m_trayIcon = new RepugnoTray();
}

QString RepugnoApplication::getJREPath()
{
    return m_jrePath;
}

QString RepugnoApplication::getI2PPath()
{
    return m_i2pPath;
}

QString RepugnoApplication::getBrowserPath()
{
    return m_abscondPath;
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
