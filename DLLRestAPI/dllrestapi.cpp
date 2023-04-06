
#include "dllrestapi.h"


DLLRestAPI::DLLRestAPI(QObject *parent):QObject(parent)
{
    qDebug()<<"DLLRestApi luotu";
    pRest = new rest(this);
}

DLLRestAPI::~DLLRestAPI()
{
qDebug()<<"DLLRestApi tuhottu";
}

bool DLLRestAPI::login(QString id, QString pin)
{
qDebug()<<"saatiin exelta kortti"<<id<<"ja pin"<<pin;
    pRest->loginAccess(id,pin);
}

