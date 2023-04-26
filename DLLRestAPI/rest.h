
#ifndef REST_H
#define REST_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>


class rest:public QObject
{
    Q_OBJECT
public:
    rest(QObject * parent = nullptr);
    ~rest();


    QByteArray getHttpResponse() const;
    void setHttpResponse(const QByteArray &newHttpResponse);

    QByteArray getToken() const;
    void setToken(const QByteArray &newToken);
    void setTilityyppi(QString);
    void setTransferInfo(QString,int);
    void setTiliTapahtuma(QString, int);





public slots:

    void loginAccess(QString,QString);
    void httpRequestSlot(QNetworkReply *reply);
    void LoginSlot(QNetworkReply *reply);
    void updateSlot(QNetworkReply * reply);
    void getMainWindowInfoAccess(QString);
    void getAccountHistory(QString);
    void getSaldo(QString); //tilitapahtumaSlotti
    void updateSaldo(QString);
    void getBlacklist(QString);

private:
    QByteArray httpResponse;       // säilöö httpresponsen serveriltä //Tämän muutin byteArreyksi
    QNetworkAccessManager * queryManager;//lähettää get pyynnön
    QNetworkAccessManager * loginManager;
    QNetworkAccessManager * updateManager;
    QNetworkReply *reply;       //säilöö http vastauksen
    QByteArray response_data;//muuttuja mitä säilöö response_datan
    QByteArray Token;
    QString tilityyppi;
    QString transaction;
    int saldoAmount;






signals:
    void httpResponseReady();
    void LoginResponseReady();
    void updateResponseReady();


};

#endif // REST_H
