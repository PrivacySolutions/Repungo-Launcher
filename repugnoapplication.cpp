#include "repugnoapplication.h"


RepugnoApplication::RepugnoApplication(int & argc, char ** argv) :
    QApplication(argc, argv)
{
    becomeSelfaware();
    createTrayIcon();
}

void RepugnoApplication::becomeSelfaware()
{
    // TODO: Move somewhere else
    const char* version = "0.1";
    setApplicationName("Repungo Launcher");
    setApplicationVersion(version);
    setOrganizationDomain("sigterm.no");
    setOrganizationName("Sigterm");
    setQuitOnLastWindowClosed(false);
#ifndef WIN32
    setenv("REPUGNO_LAUNCHER", version, 1);
#endif

}

void RepugnoApplication::createTrayIcon()
{
    trayIcon = new RepugnoTray();
}
