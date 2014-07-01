#include "repugnotray.h"
#include "repugnoapplication.h"
#include "dummyobject.h"
#include <QIcon>
#include <QAction>

RepugnoTray::RepugnoTray() : DummyObject()
{
    sysTray = new QSystemTrayIcon(QIcon(":/images/res/default256.png"));
    sysTray->setToolTip("The Abscond/Repugno project.");
    createActions();
    createMenu();
    sysTray->setContextMenu(m_stMenu);
    sysTray->setVisible(true);
}

void RepugnoTray::createActions()
{
    quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void RepugnoTray::createMenu()
{
    m_stMenu = new QMenu();
    m_stMenu->addAction(quitAction);
}
