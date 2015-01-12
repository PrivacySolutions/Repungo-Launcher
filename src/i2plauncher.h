#ifndef I2PLAUNCHER_H
#define I2PLAUNCHER_H

#include <QProcess>

#include "utils.h"
#include "repugnoapplication.h"

#define DEFAULT_MEMORY 64

// TODO: Sandboxing, see QProcess::setupChildProcess() @ http://qt-project.org/doc/qt-5/qprocess.html

class I2PLauncher : public ILauncher
{
    Q_OBJECT
public:
    I2PLauncher(QString i2pPath);
    void Run();

private:
    QString m_i2pPath;
    QString m_i2pParam;
/*
public slots:
    void handleResults(const QString &);
signals:
    void operate(const QString &);*/
};

#endif // I2PLAUNCHER_H
