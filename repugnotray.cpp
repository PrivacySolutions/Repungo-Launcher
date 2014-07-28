#include "repugnotray.h"
#include "repugnoapplication.h"
#include "childprocessthread.h"
#include "resetidentity.h"
#include <QIcon>
#include <QObject>
#include <QDebug>
#include <QAction>
#include <Qdir>

RepugnoTray::RepugnoTray() : QObject()
{
    m_sysTray = new QSystemTrayIcon(QIcon(":/images/res/default256.png"));
    m_sysTray->setToolTip("The Abscond/Repugno project.");
    createActions();
    createMenu();
    m_sysTray->setContextMenu(m_stMenu);
    m_sysTray->setVisible(true);
}

void RepugnoTray::exitApp()
{
    // For later
}

void RepugnoTray::trayLaunchMail()
{
    browserLaunch(RepugnoApplication::getBrowserParameters("-new-tab http://127.0.0.1:7657/susimail/susimail"));
}

void RepugnoTray::trayLaunchSecureMail()
{
    browserLaunch(RepugnoApplication::getBrowserParameters("-new-tab http://127.0.0.1:7657/i2pbote/index.jsp"));
}

void RepugnoTray::trayLaunchTorrents()
{
    browserLaunch(RepugnoApplication::getBrowserParameters("-new-tab http://127.0.0.1:7657/i2psnark/"));
}

void RepugnoTray::trayLaunchTorrentsPath()
{
    //TODO: Launch explorer/finder, whatever.
}

void RepugnoTray::trayResetBrowserId()
{
    ResetIdentity ri;
    ri.resetBrowserIdentity();
}

void RepugnoTray::trayLaunchBrowser()
{
    browserLaunch(RepugnoApplication::getBrowserParameters(QString("-new-window http://127.0.0.1:7657")));
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
    m_launchBrowserAction = new QAction(tr("Open browser"), this);
    connect(m_launchBrowserAction, SIGNAL(triggered()), this, SLOT(trayLaunchBrowser()));
    m_quitAction = new QAction(tr("Quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_launchMail = new QAction(tr("Open Mail"), this);
    connect(m_launchMail, SIGNAL(triggered()), this, SLOT(trayLaunchMail()));
    m_launchSecureMail = new QAction(tr("Open Secure Mail (I2P-Bote)"), this);
    connect(m_launchSecureMail, SIGNAL(triggered()), this, SLOT(trayLaunchSecureMail()));
    m_launchTorrentDirectory = new QAction(tr("Open Torrent Directory"), this);
    connect(m_launchTorrentDirectory, SIGNAL(triggered()), this, SLOT(trayLaunchTorrentsPath()));
    m_launchTorrents = new QAction(tr("Open Torrent Application"), this);
    connect(m_launchTorrents, SIGNAL(triggered()), this, SLOT(trayLaunchTorrents()));

    m_resetBrowserIdentity = new QAction(tr("Reset browser identity"), this);
    connect(m_resetBrowserIdentity, SIGNAL(triggered()), this, SLOT(trayResetBrowserId()));

}

void RepugnoTray::createMenu()
{
    m_stMenu = new QMenu();
    m_stMenu->addAction(m_launchBrowserAction);
    m_stMenu->addSeparator();
    m_stMenu->addAction(m_launchMail);
    m_stMenu->addAction(m_launchSecureMail);
    m_stMenu->addSeparator();
    m_stMenu->addAction(m_launchTorrents);
    m_stMenu->addAction(m_launchTorrentDirectory);
    m_stMenu->addSeparator();
    m_stMenu->addAction(m_quitAction);
}
