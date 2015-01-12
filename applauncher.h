#ifndef APPLAUNCHER_H
#define APPLAUNCHER_H

#include <QProcess>
#include "utils.h"

// TODO: Sandboxing, see QProcess::setupChildProcess() @ http://qt-project.org/doc/qt-5/qprocess.html

class AppLauncher : public ILauncher
{
    Q_OBJECT
public:
    AppLauncher(QString appCmdPath);
    QString getAppName();
    static void processExError(QProcess::ProcessError err);
    void Run();

private:
    void processError(QProcess::ProcessError err);

    QString cmdLine;
    QString appName;
    QProcess process;
};

#endif // APPLAUNCHER_H
