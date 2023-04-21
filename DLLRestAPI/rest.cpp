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

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(LoginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());


}


void rest::httpRequestSlot(QNetworkReply *reply)
{


    response_data=reply->readAll();
    httpResponse=response_data;
    qDebug()<<"rest.cpp sai datan "+httpResponse;
    emit httpResponseReady();
    reply->deleteLater();
    //postManager->deleteLater(); //Tämä aiheutti exen crashin

    queryManager->deleteLater();
    qDebug()<<"queryManager tuhottu";



}

void rest::LoginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
     Token="Bearer "+response_data;
     qDebug()<<"rest.cpp sai datan "+Token;
     emit LoginResponseReady();


    reply->deleteLater();
    loginManager->deleteLater();
    qDebug()<<"loginManager Tuhottu";
}

void rest::getMainWindowInfoAccess(QString cardNum)
{
    qDebug()<<"saatiin interfacelta korttiID: "<<cardNum<<" getMainWindowInfoAccessiin";

    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/kortti/"+cardNum;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(Token));
    qDebug()<<"GetMainWindowinfo: "+Token;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    queryManager = new QNetworkAccessManager(this);
    connect(queryManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = queryManager->get(request);
}

void rest::getAccountHistory(QString cardNum)       //Tilihistoria get
{
    qDebug() << "getAccount called";
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/Tilitapahtumat/"+cardNum;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(Token));
    qDebug()<<"tilitapahtumat: "+Token;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    queryManager = new QNetworkAccessManager(this);
    connect(queryManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = queryManager->get(request);
}

void rest::getSaldo(QString cardNum)    //tilin saldo get
{
    qDebug() << "getSaldo called";
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    QString site_url=Environment::getBaseUrl()+"/Tili/"+cardNum;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(Token));
    qDebug()<<"saldo: "+Token;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    queryManager = new QNetworkAccessManager(this);
    connect(queryManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = queryManager->get(request);
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





