
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

    if(QString::compare(response_data,"-4078")==0 || response_data.length()==0)
    {
        qDebug()<<"Virhe tietokantayhteydessä";
    }
    else
    {
        if(QString::compare(response_data, "false")!=0)
        {
            Token="Bearer "+response_data;
            qDebug()<<"rest.cpp sai datan "+Token;
            emit LoginResponseReady();
        }
        else
        {
            qDebug()<<"Tunnus ja salasana eivät täsmää";
        }
    }


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





