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

#define I2PMAINCLASS "net.i2p.router.RouterLaunch"
#define DEFAULT_MEMORY 128 // Maybe 128mb is too small wrt I2P-Bote, Seedless, I2PSnark etc?

// TODO: Sandboxing, see QProcess::setupChildProcess() @ http://qt-project.org/doc/qt-5/qprocess.html
/*
class I2PRunner : public DummyObject
{
public:
    I2PRunner() {
    }

    static QString i2pCommand;

public slots:
    void runI2P() {
        QString result;
        const QString cmd = I2PRunner::i2pCommand;
        process.start(cmd);
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);

private:
    QProcess process;
};*/

class I2PLauncher : public ILauncher
{
    Q_OBJECT
    //QThread workerThread;
public:
    I2PLauncher(QString jrePath, QString i2pPath);
//    I2PLauncher(QObject *parent = 0);
    /*~I2PLauncher();
    {
        workerThread.quit();
        workerThread.wait();
    }*/
    QString GenerateLaunchCommand();
    void Run();

    //const static QString cmd;

private:
    QString m_i2pPath;
    QString m_jrePath;
    QString m_jreParam;
    QString m_i2pParam;
    //I2PRunner *runner;
/*
public slots:
    void handleResults(const QString &);
signals:
    void operate(const QString &);*/
};

#endif // I2PLAUNCHER_H
