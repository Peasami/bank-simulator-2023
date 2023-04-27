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
    qDebug()<<"rest.cpp sai httpRslotilta datan  "+httpResponse;
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
     qDebug()<<"rest.cpp sai LoginSlot datan "+Token;
     emit LoginResponseReady();


    reply->deleteLater();
    loginManager->deleteLater();
    qDebug()<<"loginManager Tuhottu";
}

void rest::updateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    httpResponse=response_data;
    qDebug()<<"rest.cpp sai updateSlotin datan "+httpResponse;
    emit updateResponseReady();
    reply->deleteLater();


    updateManager->deleteLater();
    qDebug()<<"updateManager tuhottu";

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

void rest::updateSaldo(QString cardNum)
{
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);
    jsonObj.insert("tapahtumaNimi",transaction);
    jsonObj.insert("maara",saldoAmount);
    QString site_url=Environment::getBaseUrl()+"/transfer/"+tilityyppi ;
    qDebug()<<"Site_url: "<<site_url;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(Token));
    qDebug()<<"update Saldo: "+Token;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*))
            , this, SLOT(updateSlot(QNetworkReply*)));

    reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());
}

void rest::getBlacklist(QString cardNum)
{
    qDebug()<<"rest cpp:n getblacklist sai datan"<<cardNum;
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);

    QString site_url=Environment::getBaseUrl()+"/mustalista/check/";
    qDebug()<<"get blacklist"<<site_url;
    QNetworkRequest request((site_url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*))
            , this, SLOT(updateSlot(QNetworkReply*)));

    reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());
}

void rest::updateBlacklist(QString cardNum)
{
    qDebug()<<"rest cpp vie blacklist datan "<<cardNum;
    QJsonObject jsonObj;
    jsonObj.insert("idKortti",cardNum);

    QString site_url=Environment::getBaseUrl()+"/mustalista/";
    qDebug()<<"get blacklist "<<site_url;
    QNetworkRequest request((site_url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*))
            , this, SLOT(updateSlot(QNetworkReply*)));

    reply = updateManager->post(request, QJsonDocument(jsonObj).toJson());
}




QByteArray rest::getToken() const
{
    return Token;
}

void rest::setToken(const QByteArray &newToken)
{
    Token = newToken;
}

void rest::setTilityyppi(QString tili)
{
    tilityyppi = tili;
    qDebug()<<"r"<< tili;
}

void rest::setTiliTapahtuma(QString tapahtuma, int summa)
{
    transaction = tapahtuma;
    saldoAmount = summa;
    qDebug()<<"rest.cpp sai tapahtuman tiedot: " <<tapahtuma<<summa;
}





QByteArray rest::getHttpResponse() const
{
    return httpResponse;
}

void rest::setHttpResponse(const QByteArray &newHttpResponse)
{
    httpResponse = newHttpResponse;
}





