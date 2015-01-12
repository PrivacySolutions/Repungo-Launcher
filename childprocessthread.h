#ifndef CHILDPROCESSTHREAD_H
#define CHILDPROCESSTHREAD_H

#include <QThread>
#include "utils.h"

class ChildProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit ChildProcessThread(QObject *parent = 0, ILauncher *process = NULL, bool b = false);
    void run();

    bool isRunning;
signals:
    void stateChanged(bool);
public slots:

private:
    ILauncher *currentProcess;
};

#endif // CHILDPROCESSTHREAD_H
