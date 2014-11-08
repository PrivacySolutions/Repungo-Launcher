#ifndef I2PLAUNCHER_H
#define I2PLAUNCHER_H

//#include <QThread>
#include <QProcess>

/*
class Constants{
public:
    static const QString i2pRunCommand;
};*/

#include "dummyobject.h"
#include "ilauncher.h"
#include "repugnoapplication.h"
#include "i2pmonitor.h"

#define I2PMAINCLASS "net.i2p.router.RouterLaunch"
#define DEFAULT_MEMORY 128 // Maybe 128mb is too small wrt I2P-Bote, Seedless, I2PSnark etc?

// TODO: Sandboxing, see QProcess::setupChildProcess() @ http://qt-project.org/doc/qt-5/qprocess.html

class I2PLauncher : public ILauncher
{
    Q_OBJECT
    //QThread workerThread;
public:
    I2PLauncher(I2PMonitor *m, QString i2pPath);
//    I2PLauncher(QObject *parent = 0);
    /*~I2PLauncher();
    {
        workerThread.quit();
        workerThread.wait();
    }*/
    //QString GenerateLaunchCommand();
    void Run();

    //const static QString cmd;

private:
    QString m_i2pPath;
    QString m_i2pParam;
    //I2PRunner *runner;
    I2PMonitor *m_monitorObject;

/*
public slots:
    void handleResults(const QString &);
signals:
    void operate(const QString &);*/
};

#endif // I2PLAUNCHER_H
