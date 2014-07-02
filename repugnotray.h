#ifndef REPUGNOTRAY_H
#define REPUGNOTRAY_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

#include "dummyobject.h"

// Note:
// Adding a abstract layer towards QSystemTrayIcon now, because
// I know with Qt that it could be handy for later.
class RepugnoTray : DummyObject
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
    QAction *restartI2PAction;
    QAction *quitAction;

    QSystemTrayIcon *sysTray;
    QMenu *m_stMenu;
private slots:
    void exitApp();
};

#endif // REPUGNOTRAY_H
