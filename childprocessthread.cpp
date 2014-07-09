#include "childprocessthread.h"

ChildProcessThread::ChildProcessThread(QObject *parent, ILauncher *process, bool b) :
    QThread(parent), isRunning(b), currentProcess(process)
{
}

void ChildProcessThread::run()
{
    currentProcess->Run();
}
