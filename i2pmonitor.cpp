#include "i2pmonitor.h"

I2PMonitor::I2PMonitor(QObject *parent) :
    QObject(parent)
{
}
/*
 * Pseudo code, to be extended
I2PMonitor::I2PMonitor *instance()
{
    if (self == NULL)
    {
        self = new I2PMonitor();
    }
    return this;
}
*/
