
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

void DLLRestAPI::getAccountHistoryInfo(QString cardNum) //tilitapahtuma tieto
{
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(accountHistorySlot()));
    pRest->getAccountHistory(cardNum);
}

void DLLRestAPI::getSaldoInfo(QString cardNum)      //Tilin Saldon tiedot
{
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(getSaldoSlot()));
    pRest->getSaldo(cardNum);
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
    delete pRest;
    pRest=nullptr;
}

void DLLRestAPI::httpReadySlot()
{

    httpResponse = pRest->getHttpResponse();
    qDebug()<<"httpReadySlot: "<<httpResponse;
    emit httpReady();
    delete pRest;
    pRest=nullptr;
}

void DLLRestAPI::accountHistorySlot()   //Slotti Tilitapahtuma
{
     httpResponse = pRest->getHttpResponse();
     //qDebug()<<"accountHistorySlotissa kayty ";
     emit accountHistorySignal();           //Signaali joka menisi exelle.



}

void DLLRestAPI::getSaldoSlot()
{

    httpResponse = pRest->getHttpResponse();
   // qDebug()<<"getSaldoSlotissa kayty: ";
    emit getSaldoSignal();



}



const QByteArray &DLLRestAPI::getHttpResponse() const
{
    //qDebug()<<"getHttpResponse: "<<httpResponse;
    return httpResponse;
}
