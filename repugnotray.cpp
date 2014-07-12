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

void RepugnoTray::trayLaunchBrowser()
{
#ifdef Q_OS_MAC
    QString *temp = new QString(RepugnoApplication::applicationDirPath()+QDir::separator()+"firefox "+RepugnoApplication::getBrowserParameters());
#else
#ifdef WIN32
    QString *temp = new QString(RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox.exe "+RepugnoApplication::getBrowserParameters());
#else
    QString *temp = new QString(RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox "+RepugnoApplication::getBrowserParameters());
#endif
    qDebug() << "Trying to launch: " << RepugnoApplication::applicationDirPath()+QDir::separator()+"Browser"+QDir::separator()+"firefox "+RepugnoApplication::getBrowserParameters();
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
