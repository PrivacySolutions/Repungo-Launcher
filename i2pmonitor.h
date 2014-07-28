#ifndef I2PMONITOR_H
#define I2PMONITOR_H

#include <QObject>

class I2PMonitor : public QObject
{
    Q_OBJECT
public:
    explicit I2PMonitor(QObject *parent = 0);
//TODO: Convert to QT's signal & slots
    void setI2PStatus(bool s) { m_isI2PAlive = s; }
    bool getI2PStatus() { return m_isI2PAlive; }
/*    static I2PMonitor *instance();

signals:

public slots:

private:
    static I2PMonitor self;*/
    bool m_isI2PAlive = false;
};

#endif // I2PMONITOR_H
