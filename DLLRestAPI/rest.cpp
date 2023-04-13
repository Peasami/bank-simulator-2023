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
    postManager->deleteLater();

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

QByteArray rest::getToken() const
{
    return Token;
}

void rest::setToken(const QByteArray &newToken)
{
    Token = newToken;
}

QString rest::getHttpResponse() const
{
    return httpResponse;
}

void rest::setHttpResponse(const QString &newHttpResponse)
{
    httpResponse = newHttpResponse;
}





