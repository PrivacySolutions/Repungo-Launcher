#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QString>
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
    void tellAboutTheFuckup(QString title, QString msg);
    bool getI2PStatus();
    void setI2PStatus(bool status);

private:
    void becomeSelfaware();
    void rememberLastNight();
    void locateI2P();
    void locateJRE();
    void locateAbscond();
    void createTrayIcon();
    void configReset();

    // I2P Monitoring
    // TODO: Make thread safe
    bool *m_isI2PAlive;

    QString m_jrePath;
    QString m_i2pPath;
    QString m_abscondPath;

    RepugnoTray *m_trayIcon;
    QSettings *m_longtermMemory;

};

#endif // REPUGNOAPPLICATION_H
