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

    QAction *aboutApplicationAction;
    QAction *restartBrowserAction;
    QAction *launchBrowserAction;
    QAction *restartI2PAction;
    QAction *quitAction;

    QSystemTrayIcon *sysTray;
    QMenu *m_stMenu;
public slots:
    void trayLaunchTorrents();
    void trayLaunchTorrentsPath();
    void trayLaunchMail();
    void trayLaunchSecureMail();
    void trayLaunchBrowser();
    void exitApp();
};

#endif // REPUGNOTRAY_H
