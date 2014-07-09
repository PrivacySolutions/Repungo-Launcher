#include "repugnotray.h"
#include "repugnoapplication.h"
#include "dummyobject.h"
#include <QIcon>
#include <QAction>
#include <Qdir>

RepugnoTray::RepugnoTray() : DummyObject()
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

void RepugnoTray::launchBrowser()
{
    QString *temp = new QString(RepugnoApplication::applicationDirPath()+QDir::separator()+"firefox "+RepugnoApplication::getBrowserParameters());
    AppLauncher *al = new AppLauncher(temp);
    delete temp; //TODO Keep track of al and cleanup
}

void RepugnoTray::createActions()
{
    launchBrowserAction = new QAction(tr("Open browser"), this);
    connect(launchBrowserAction, SIGNAL(triggered(), this, SLOT(launchBrowser()));
    quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void RepugnoTray::createMenu()
{
    m_stMenu = new QMenu();
    m_stMenu->addAction(launchBrowserAction);
    m_stMenu->addAction(quitAction);
}
