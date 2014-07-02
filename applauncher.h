#ifndef APPLAUNCHER_H
#define APPLAUNCHER_H

#include <QProcess>
#include "dummyobject.h"

// TODO: Sandboxing, see QProcess::setupChildProcess() @ http://qt-project.org/doc/qt-5/qprocess.html

class AppLauncher : DummyObject
{
    Q_OBJECT
public:
    AppLauncher(QString *appCmdPath);
    QString getAppName();
    static void processExError(QProcess::ProcessError err);

private:
    void processError(QProcess::ProcessError err);

    QString appName;
    QProcess process;
};

#endif // APPLAUNCHER_H
