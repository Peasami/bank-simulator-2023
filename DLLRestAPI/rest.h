
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


    QString getHttpResponse() const;
    void setHttpResponse(const QString &newHttpResponse);

    QByteArray getToken() const;
    void setToken(const QByteArray &newToken);

public slots:

    void loginAccess(QString,QString);
    void httpRequestSlot(QNetworkReply *reply);
    void LoginSlot(QNetworkReply *reply);
private:
    QString httpResponse;       //säilöö httpresponsen serveriltä
    QNetworkAccessManager *postManager;     //lähetää post pyynnön
    QNetworkReply *reply;       //säilöö http vastauksen
    QByteArray response_data;//muuttuja mitä säilöö response_datan
    QByteArray Token;
signals:
    void httpResponseReady();
    void LoginResponseReady();
};

#endif // REST_H
