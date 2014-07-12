#include "dummyobject.h"
#include <QDebug>
#include <QCoreApplication>

// This dummy object gives access to all native QT stuff on own custom classes. Really handy.

DummyObject::DummyObject (QObject *parent) :
    QObject (parent)
{
    qDebug() << "ctor";
}


DummyObject::~DummyObject()
{
    qDebug() << "dtor";
}


