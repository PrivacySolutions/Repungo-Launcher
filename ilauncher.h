#ifndef ILAUNCHER_H
#define ILAUNCHER_H

#include <QObject>

#include "dummyobject.h"

/*
The idea:
This is a interface for a "application runner" that works both for AppLancher and I2PLauncher.
This way opens for passing one of them abstract into a new thread class, making them fork into
a own thread inside the application before starting up the child process.
*/

class ILauncher : public DummyObject
{
public:
    virtual void Run()= 0;
};

#endif // ILAUNCHER_H
