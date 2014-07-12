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
public:
    RepugnoTray();
private:
    void createActions();
    void createMenu();
    void showMessage();
    void messageClicked();

    QAction *aboutApplicationAction;
    QAction *restartBrowserAction;
    QAction *launchBrowserAction;
    QAction *restartI2PAction;
    QAction *quitAction;

    QSystemTrayIcon *sysTray;
    QMenu *m_stMenu;
public slots:
    void trayLaunchBrowser();
    void exitApp();
};

#endif // REPUGNOTRAY_H
