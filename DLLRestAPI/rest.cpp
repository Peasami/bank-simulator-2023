
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
    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());


}


void rest::httpRequestSlot(QNetworkReply *reply)
    {
    response_data=reply->readAll();

    httpResponse="Bearer " +response_data;
    httpResponse=response_data;
    //emit httpResponseReady();
    reply->deleteLater();
    postManager->deleteLater();
    qDebug()<<httpResponse;
    }

    QString rest::getHttpResponse() const
    {
    return httpResponse;
    }

    void rest::setHttpResponse(const QString &newHttpResponse)
    {
    httpResponse = newHttpResponse;
    }

    void rest::sendLoginResponse(bool)
    {

    }



