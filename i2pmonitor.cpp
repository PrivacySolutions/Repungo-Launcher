#include "i2pmonitor.h"

I2PMonitor::I2PMonitor(QObject *parent) :
    QObject(parent)
{
}
/*
 * Old java pseudo code, to be removed
I2PMonitor::I2PMonitor *instance()
{
    if (self == NULL)
    {
        self = new I2PMonitor();
    }
    return this;
}
*/
