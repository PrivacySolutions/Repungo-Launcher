#include "repugnotray.h"
#include "repugnoapplication.h"
#include "childprocessthread.h"
#include <QIcon>
#include <QObject>
#include <QDebug>
#include <QAction>
#include <Qdir>

RepugnoTray::RepugnoTray() : QObject()
{
    sysTray = new QSystemTrayIcon(QIcon(":/images/res/default256.png"));
    sysTray->setToolTip("The Abscond/Repugno project.");
    createActions();
    createMenu();
    sysTray->setContextMenu(m_stMenu);
    sysTray->setVisible(true);
}

void RepugnoTray::exitApp()
{
    // For later
}

void RepugnoTray::trayLaunchMail()
{}

void RepugnoTray::trayLaunchSecureMail()
{}

void RepugnoTray::trayLaunchTorrents()
{}

void RepugnoTray::trayLaunchTorrentsPath()
{}

void RepugnoTray::trayLaunchBrowser()
{
    browserLaunch(RepugnoApplication::getBrowserParameters());
}

void RepugnoTray::browserLaunch(QString params)
{
#ifdef Q_OS_MAC
    QString temp(RepugnoApplication::applicationDirPath()+QDir::separator()+"firefox "+params);
#else
#ifdef WIN32
    QString temp(RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox.exe "+params);
#else
    QString temp(RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox "+params);
#endif
    qDebug() << "Trying to launch: " << RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox "+params;
#endif
    AppLauncher *al = new AppLauncher(temp);
    ChildProcessThread *cpt = new ChildProcessThread(NULL, al, false);
    cpt->start();
}

void RepugnoTray::createActions()
{
    launchBrowserAction = new QAction(tr("Open browser"), this);
    connect(launchBrowserAction, SIGNAL(triggered()), this, SLOT(trayLaunchBrowser()));
    quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void RepugnoTray::createMenu()
{
    m_stMenu = new QMenu();
    m_stMenu->addAction(launchBrowserAction);
    m_stMenu->addAction(quitAction);
}
