
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
public slots:

    void sendLoginResponse(bool);
    void loginAccess(QString,QString);
private:
    QString httpResponse;       //säilöö httpresponsen serveriltä
    QNetworkAccessManager *postManager;     //lähetää post pyynnön
    QNetworkReply *reply;       //säilöö http vastauksen
    QByteArray response_data;   //muuttuja mitä säilöö response_datan
};

#endif // REST_H
