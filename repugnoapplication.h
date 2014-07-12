#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include "version.h"
#include "repugnotray.h"
#include "applauncher.h"
#include "i2plauncher.h"

class RepugnoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit RepugnoApplication(int & argc, char ** argv);
    QString getJREPath();
    QString getI2PPath();
    QString getBrowserPath();
    static QString getBrowserParameters();
    void LaunchBrowser();
    void InitAll();

signals:

private:
    void becomeSelfaware();
    void rememberLastNight();
    void locateI2P();
    void locateJRE();
    void locateAbscond();
    void createTrayIcon();
    void configReset();

    QString jrePath;
    QString i2pPath;
    QString abscondPath;

    RepugnoTray *trayIcon;
    QSettings *longtermMemory;

public slots:

};

#endif // REPUGNOAPPLICATION_H
