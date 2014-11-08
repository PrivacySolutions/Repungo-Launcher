#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QString>
#include "version.h"
#include "repugnotray.h"
#include "applauncher.h"
#include "i2plauncher.h"
#include "i2pmonitor.h"

class RepugnoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit RepugnoApplication(int & argc, char ** argv);
    QString getI2PPath();
    QString getBrowserPath();
    static QString getBrowserParameters(QString concat, bool init = false);
    void LaunchBrowser();
    void InitAll();
    void tellAboutTheFuckup(QString title, QString msg);


private:
    void becomeSelfaware();
    void rememberLastNight();
    void locateI2P();
    void locateAbscond();
    void createTrayIcon();
    void configReset();

    QString m_i2pPath;
    QString m_abscondPath;

    RepugnoTray *m_trayIcon;
    QSettings *m_longtermMemory;
    I2PMonitor *m_i2pMonitor;

};

#endif // REPUGNOAPPLICATION_H
