#ifndef REPUGNOAPPLICATION_H
#define REPUGNOAPPLICATION_H

#include <QApplication>
#include "repugnotray.h"

class RepugnoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit RepugnoApplication(int & argc, char ** argv);

signals:

private:
    void becomeSelfaware();
    void createTrayIcon();

    RepugnoTray *trayIcon;


public slots:

};

#endif // REPUGNOAPPLICATION_H
