#include <QCoreApplication>
#include "repugnoapplication.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    RepugnoApplication a(argc, argv);

    return a.exec();
}
