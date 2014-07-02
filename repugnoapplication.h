#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include <QSettings>
#include "repugnotray.h"

class RepugnoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit RepugnoApplication(int & argc, char ** argv);

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
