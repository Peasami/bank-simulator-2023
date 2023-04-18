#include "enviroment.h"
#include "rest.h"


rest::rest(QObject *parent):QObject(parent)
{
    qDebug()<<"rest luotu";


}

rest::~rest()
{
    qDebug()<<"rest tuhottu";
}


void rest::loginAccess(QString idKortti, QString PINkoodi)
{
    qDebug()<<"saatin interfacelta kortti"<<idKortti<<"ja pin"<<PINkoodi;

    QJsonObject jsonObj;
    jsonObj.insert("idKortti",idKortti);
    jsonObj.insert("PINkoodi",PINkoodi);
    QString site_url=Environment::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(LoginSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());


}


void rest::httpRequestSlot(QNetworkReply *reply)
{


    response_data=reply->readAll();
    httpResponse=response_data;
    qDebug()<<"rest.cpp sai datan "+httpResponse;
    emit httpResponseReady();
    reply->deleteLater();
    //postManager->deleteLater(); //Tämä aiheutti exen crashin

    switch(state)
    {
    case GETMANAGER:
        qDebug()<<"getManager tuhottu";
        getManager->deleteLater();
        break;
    case GETSALDOMANAGER:
        qDebug()<<"getSaldoManager tuhottu";
        getSaldoManager->deleteLater();
        break;
    case GETACCOUNTMANAGER:
        qDebug()<<"getAccountManager tuhottu";
        getAccountManager->deleteLater();
        break;
    }



}

void rest::LoginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
     Token="Bearer "+response_data;
     qDebug()<<"rest.cpp sai datan "+Token;
     emit LoginResponseReady();


    reply->deleteLater();
    postManager->deleteLater();
}

void rest::getMainWindowInfoAccess(QString cardNum)
{
    qDebug()<<"saatiin interfacelta korttiID: "<<cardNum<<" getMainWindowInfoAccessiin";

    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/kortti/"+cardNum;
    //QByteArray myToken="Bearer "+response_data;
    //request.setRawHeader(QByteArray("Authorization"),(myToken));
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = getManager->get(request);

    state = GETMANAGER;
}

void rest::getAccountHistory(QString cardNum)       //Tilihistoria get
{
    qDebug() << "getAccount called";
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/Tilitapahtumat/"+cardNum;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    //QByteArray myToken="Bearer "+response_data;
    //request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getAccountManager = new QNetworkAccessManager(this);
    connect(getAccountManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = getAccountManager->get(request);

    state = GETACCOUNTMANAGER;
}

void rest::getSaldo(QString cardNum)    //tilin saldo get
{
    qDebug() << "getSaldo called";
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/Tili/"+cardNum;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    //QByteArray myToken="Bearer "+response_data;
    //request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getSaldoManager = new QNetworkAccessManager(this);
    connect(getSaldoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = getSaldoManager->get(request);

    state = GETSALDOMANAGER;
}




QByteArray rest::getToken() const
{
    return Token;
}

void rest::setToken(const QByteArray &newToken)
{
    Token = newToken;
}

QByteArray rest::getHttpResponse() const
{
    return httpResponse;
}

void rest::setHttpResponse(const QByteArray &newHttpResponse)
{
    httpResponse = newHttpResponse;
}





