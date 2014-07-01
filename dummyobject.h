#ifndef DUMMYOBJECT_H
#define DUMMYOBJECT_H

#include <QObject>
#include <QNetworkReply>


class DummyObject : public QObject
{
    Q_OBJECT

  public:
    DummyObject (QObject *parent = 0);
    ~DummyObject();

  private:

};


#endif // DUMMYOBJECT_H
