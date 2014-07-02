#include "applauncher.h"
#include <QFile>
#include <QMessageBox>

AppLauncher::AppLauncher(QString *appCmdPath) : DummyObject()
{
    //connect error() to slot processError() to get error, if occurs.
    QObject::connect( &process, SIGNAL(error(QProcess::ProcessError)),
                          this, SLOT(processError(QProcess::ProcessError)));

    // Get executable's name
    QFile *f = new QFile(*appCmdPath);
    appName = f->fileName();
    delete f;

    //pass the name of executable that's gonna launch.
    process.start(*appCmdPath);
}

QString AppLauncher::getAppName()
{
    return appName;
}

//get errors, if any
void AppLauncher::processError(QProcess::ProcessError err)
{
    switch(err)
    {
    case QProcess::FailedToStart:
        QMessageBox::information(0,"FailedToStart","("+appName+"): FailedToStart");
        break;
    case QProcess::Crashed:
        QMessageBox::information(0,"Crashed","("+appName+"): Crashed");
        break;
    case QProcess::Timedout:
        QMessageBox::information(0,"FailedToStart","("+appName+"): FailedToStart");
        break;
    case QProcess::WriteError:
        QMessageBox::information(0,"Timedout","("+appName+"): Timedout");
        break;
    case QProcess::ReadError:
        QMessageBox::information(0,"ReadError","("+appName+"): ReadError");
        break;
    case QProcess::UnknownError:
        QMessageBox::information(0,"UnknownError","("+appName+"): UnknownError");
        break;
    default:
        QMessageBox::information(0,"default","("+appName+"): default");
        break;
    }
}

void AppLauncher::processExError(QProcess::ProcessError err)
{
    switch(err)
    {
    case QProcess::FailedToStart:
        QMessageBox::information(0,"FailedToStart","FailedToStart");
        break;
    case QProcess::Crashed:
        QMessageBox::information(0,"Crashed","Crashed");
        break;
    case QProcess::Timedout:
        QMessageBox::information(0,"FailedToStart","FailedToStart");
        break;
    case QProcess::WriteError:
        QMessageBox::information(0,"Timedout","Timedout");
        break;
    case QProcess::ReadError:
        QMessageBox::information(0,"ReadError","ReadError");
        break;
    case QProcess::UnknownError:
        QMessageBox::information(0,"UnknownError","UnknownError");
        break;
    default:
        QMessageBox::information(0,"default","default");
        break;
    }
}
