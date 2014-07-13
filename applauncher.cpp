#include "applauncher.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>

// NOTE: windows.h MUST be loaded _before_ stdio.h if not error

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>

#ifdef WIN32
#include <string.h>
#include "i2plauncher.h"
extern LPWSTR ConvertToLPWSTR( const std::string& s );
#endif


AppLauncher::AppLauncher(QString appCmdPath)
{
    cmdLine = appCmdPath;
}

QString AppLauncher::getAppName()
{
    return appName;
}

void AppLauncher::Run()
{
    //connect error() to slot processError() to get error, if occurs.
   /* QObject::connect( &process, SIGNAL(error(QProcess::ProcessError)),
                          this, SLOT(processError(QProcess::ProcessError)));
*/
    // Get executable's name
    appName = QFile(cmdLine).fileName();


#ifdef WIN32

#include <stdlib.h>

#if WINVER == 0x0602
// Why?
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx
// http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745(v=vs.85).aspx#macros_for_conditional_declarations
#include "Processthreadsapi.h"
#endif
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    if( !CreateProcess( NULL,   // No module name (use command line)
        ConvertToLPWSTR(cmdLine.toStdString()),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW, // Don't show console to the end user.
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
        return;
    }
    WaitForSingleObject( pi.hProcess, INFINITE );

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
#else

    //pass the name of executable that's gonna launch.
    process.start(cmdLine);
#endif
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
