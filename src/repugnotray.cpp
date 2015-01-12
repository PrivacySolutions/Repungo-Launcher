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
    m_sysTray = new QSystemTrayIcon(QIcon(":/images/res/default256.png"));
    m_sysTray->setToolTip("The Abscond browser bundle project (Repugno Launcher)");
    createActions();
    createMenu();
    m_sysTray->setContextMenu(m_stMenu);
    m_sysTray->setVisible(true);
}

void RepugnoTray::exitApp()
{
    // For later
}

#ifdef BUILD_WITH_BROWSER
void RepugnoTray::trayResetBrowserId()
{
    ResetIdentity ri;
    ri.resetBrowserIdentity();
}

void RepugnoTray::trayLaunchBrowser()
{
    browserLaunch(RepugnoApplication::getBrowserParameters(QString("-new-window http://127.0.0.1:7070"), true));
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
#endif

void RepugnoTray::createActions()
{
#ifdef BUILD_WITH_BROWSER
    m_launchBrowserAction = new QAction(tr("Open browser"), this);
    connect(m_launchBrowserAction, SIGNAL(triggered()), this, SLOT(trayLaunchBrowser()));
    m_resetBrowserIdentity = new QAction(tr("Reset browser identity"), this);
    connect(m_resetBrowserIdentity, SIGNAL(triggered()), this, SLOT(trayResetBrowserId()));
#endif
    m_quitAction = new QAction(tr("Quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

}

void RepugnoTray::createMenu()
{
    m_stMenu = new QMenu();
#ifdef BUILD_WITH_BROWSER
    m_stMenu->addAction(m_launchBrowserAction);
    m_stMenu->addSeparator();
#endif
    m_stMenu->addAction(m_quitAction);
}
