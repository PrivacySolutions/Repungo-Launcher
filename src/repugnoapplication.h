#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include <QString>
#include "repugnotray.h"
#include "applauncher.h"
#include "i2plauncher.h"

class RepugnoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit RepugnoApplication(int & argc, char ** argv);
    QString getI2PPath();
#ifdef BUILD_WITH_BROWSER
    QString getBrowserPath();
    static QString getBrowserParameters(QString concat, bool init = false);
    void LaunchBrowser();
#endif
    void tellAboutTheFuckup(QString title, QString msg);


private:
    void becomeSelfaware();
    void rememberLastNight();
    void locateI2P();
#ifdef BUILD_WITH_BROWSER
    void locateAbscond();
#endif
    void createTrayIcon();
    void configReset();

    QString m_i2pPath;
#ifdef BUILD_WITH_BROWSER
    QString m_abscondPath;
#endif

    RepugnoTray m_trayIcon;
    QSettings m_longtermMemory;

};

#endif // REPUGNOAPPLICATION_H
