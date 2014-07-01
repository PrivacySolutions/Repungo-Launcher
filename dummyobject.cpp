#include "dummyobject.h"
#include <QDebug>
#include <QCoreApplication>
#include <QNetworkRequest>


DummyObject::DummyObject (QObject *parent) :
    QObject (parent)
{
    qDebug() << "ctor";
}


DummyObject::~DummyObject()
{
    qDebug() << "dtor";
}


