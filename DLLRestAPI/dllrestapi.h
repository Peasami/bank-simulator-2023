
#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QDebug>
#include<QObject>
#include "DLLRestAPI_global.h"
#include "rest.h"

class DLLRESTAPI_EXPORT DLLRestAPI: public QObject
{
    Q_OBJECT
public:
    DLLRestAPI(QObject * parent = nullptr);
    ~DLLRestAPI();
public slots:
    bool login(QString,QString);


signals:
    void sendLoginReplySignal(bool);
private:
    rest * pRest;
};


#endif // DLLRESTAPI_H
