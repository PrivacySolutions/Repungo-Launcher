#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class DummyObject : public QObject
{
    Q_OBJECT

  public:
    DummyObject (QObject *parent = 0);
    ~DummyObject();

  private:

};

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

bool is_alive (const char *ipaddr, unsigned short port, int timeout);

#endif // UTILS_H
