#include "childprocessthread.h"

#include <QMutex>

ChildProcessThread::ChildProcessThread(QObject *parent, ILauncher *process, bool b) :
    QThread(parent), isRunning(b), currentProcess(process)
{
}

void ChildProcessThread::run()
{
    // TODO
    QMutex mutex;
    mutex.lock();
    currentProcess->Run();
    emit stateChanged(true);
    mutex.unlock();
    // emit stateChanged(false);
}
