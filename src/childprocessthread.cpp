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
    emit stateChanged(true);
    currentProcess->Run();
    emit stateChanged(false);
    mutex.unlock();
    // emit stateChanged(false);
}
