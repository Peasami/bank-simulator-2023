
#include "dllrestapi.h"


DLLRestAPI::DLLRestAPI(QObject *parent):QObject(parent)
{
    qDebug()<<"DLLRestApi luotu";
    pRest = new rest(this);
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(getSaldoSlot()));

    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(accountHistorySlot()));

    connect(pRest, SIGNAL(updateResponseReady()),
            this,SLOT(updateSaldoSlot()));

    connect(pRest, SIGNAL(updateResponseReady()),
            this,SLOT(blacklistSlot()));
    /*
    connect(pRest, SIGNAL(updateResponseReady()),
            this,SLOT(updateBlacklistSlot()));
            */
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

void DLLRestAPI::getAccountHistoryInfo(QString cardNum)//,QByteArray token) //tilitapahtuma tieto
{
    //pRest->setToken(token);
    pRest->getAccountHistory(cardNum);

}

void DLLRestAPI::getSaldoInfo(QString cardNum)      //Tilin Saldon tiedot
{

    pRest->getSaldo(cardNum);
}

void DLLRestAPI::updateSaldoInfo(QString cardNum)
{
    pRest->updateSaldo(cardNum);
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
    //delete pRest;
    //pRest=nullptr;
}

void DLLRestAPI::httpReadySlot()
{

    httpResponse = pRest->getHttpResponse();
    qDebug()<<"httpReadySlot: "<<httpResponse;
    emit httpReady();
    //delete pRest;
    //pRest=nullptr;
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

void DLLRestAPI::updateSaldoSlot()
{
    httpResponse = pRest->getHttpResponse();
    emit updateSaldoSignal();
}


void DLLRestAPI::blacklistSlot()
{
    httpResponse = pRest->getHttpResponse();
    emit blacklistSignal();
}
/*
void DLLRestAPI::updateBlacklistSlot()
{
    httpResponse = pRest->getHttpResponse();
    emit updateBlacklistSignal();
}
*/
void DLLRestAPI::getTilityyppi(QString tili)
{
    tilityyppi = tili;
    pRest->setTilityyppi(tili);
    qDebug()<<"Tilityypi saatu: "<<tili;

}

void DLLRestAPI::receiveTransfer(QString tapahtuma, int summa)

{
    tapahtumaNimi = tapahtuma;
    pRest->setTiliTapahtuma(tapahtuma,summa);
    qDebug() << "rest api sai transferin:" << tapahtuma<< summa;


}

void DLLRestAPI::checkBlacklist(QString cardNum)
{
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(httpReadySlot()));
    pRest->getBlacklist(cardNum);
}

void DLLRestAPI::addToBlacklist(QString cardNum)
{
    connect(pRest,SIGNAL(httpResponseReady()),
            this,SLOT(httpReadySlot()));
    pRest->updateBlacklist(cardNum);
}




const QByteArray &DLLRestAPI::getHttpResponse() const
{
    //qDebug()<<"getHttpResponse: "<<httpResponse;
    return httpResponse;
}
