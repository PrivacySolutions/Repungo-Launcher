#ifndef REPUGNOTRAY_H
#define REPUGNOTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

#include "dummyobject.h"

// Note:
// Adding a abstract layer towards QSystemTrayIcon now, because
// I know with Qt that it could be handy for later.
class RepugnoTray : public QObject
{
    Q_OBJECT
public:
    RepugnoTray();
private:
    void createActions();
    void createMenu();
    void showMessage();
    void messageClicked();
    void browserLaunch(QString params);

    QAction *m_launchTorrents;
    QAction *m_launchTorrentDirectory;
    QAction *m_launchSecureMail;
    QAction *m_launchMail;

    QAction *m_resetBrowserIdentity;

    QAction *m_aboutApplicationAction;
    QAction *m_restartBrowserAction;
    QAction *m_launchBrowserAction;
    QAction *m_restartI2PAction;
    QAction *m_quitAction;

    QSystemTrayIcon *m_sysTray;
    QMenu *m_stMenu;
public slots:
    void trayLaunchTorrents();
    void trayLaunchTorrentsPath();
    void trayLaunchMail();
    void trayLaunchSecureMail();
    void trayLaunchBrowser();
    void exitApp();

    void trayResetBrowserId();
};

#endif // REPUGNOTRAY_H
