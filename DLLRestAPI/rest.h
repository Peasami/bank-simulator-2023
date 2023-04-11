
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

public slots:
    void sendLoginResponse(bool);
    void loginAccess(QString,QString);
    void httpRequestSlot(QNetworkReply *reply);
private:
    QString httpResponse;       //säilöö httpresponsen serveriltä
    QNetworkAccessManager *postManager;     //lähetää post pyynnön
    QNetworkReply *reply;       //säilöö http vastauksen
    QByteArray response_data;//muuttuja mitä säilöö response_datan
signals:
    void httpResponseReady();
};

#endif // REST_H
