
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

void DLLRestAPI::login(QString id, QString pin)
{
    connect(pRest,SIGNAL(LoginResponseReady()),
            this,SLOT(loginReadySlots()));
    qDebug()<<"saatiin exelta kortti"<<id<<"ja pin"<<pin;
    pRest->loginAccess(id,pin);

}

void DLLRestAPI::getMainwindowInfo(QString cardNum)
{
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(httpReadySlot()));
    pRest->getMainWindowInfoAccess(cardNum);
}


const QString &DLLRestAPI::getLoginResponse() const
{
    return loginResponse;
}

void DLLRestAPI::setLoginResponse(const QString &newLoginResponse)
{
    loginResponse = newLoginResponse;
}

void DLLRestAPI::loginReadySlots()
{
    loginResponse=pRest->getToken();
    emit loginReady();
}

void DLLRestAPI::httpReadySlot()
{

    httpResponse = pRest->getHttpResponse();
    qDebug()<<"httpReadySlot: "<<httpResponse;
    emit httpReady();
}

const QString &DLLRestAPI::getHttpResponse() const
{
    qDebug()<<"getHttpResponse: "<<httpResponse;
    return httpResponse;
}
