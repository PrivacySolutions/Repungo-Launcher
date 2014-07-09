#include <QCoreApplication>
#include "repugnoapplication.h"

#ifdef WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    int argc = 0;
#else
int main(int argc, char *argv[])
{
#endif
    Q_INIT_RESOURCE(resources);
#ifdef WIN32
    RepugnoApplication a(argc, 0);
#else
    RepugnoApplication a(argc, argv);
#endif
    return a.exec();
}
