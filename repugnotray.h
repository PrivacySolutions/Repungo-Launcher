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
#ifdef BUILD_WITH_BROWSER
    void browserLaunch(QString params);
#endif

#ifdef BUILD_WITH_BROWSER
    QAction *m_resetBrowserIdentity;
#endif

    QAction *m_aboutApplicationAction;
#ifdef BUILD_WITH_BROWSER
    QAction *m_restartBrowserAction;
    QAction *m_launchBrowserAction;
#endif
    QAction *m_restartI2PAction;
    QAction *m_quitAction;

    QSystemTrayIcon *m_sysTray;
    QMenu *m_stMenu;
public slots:
#ifdef BUILD_WITH_BROWSER
    void trayLaunchBrowser();
    void trayResetBrowserId();
#endif
    void exitApp();
};

#endif // REPUGNOTRAY_H
