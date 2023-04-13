
#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QDebug>
#include<QObject>
#include "DLLRestAPI_global.h"
#include "rest.h"

class DLLRESTAPI_EXPORT DLLRestAPI: public QObject
{
    Q_OBJECT
public:
    DLLRestAPI(QObject * parent = nullptr);
    ~DLLRestAPI();
    const QString &getLoginResponse() const;
    void setLoginResponse(const QString &newLoginResponse);

    //const QString &getToken() const;
    //void setToken(const QString &newToken);

    const QString &getHttpResponse() const;

public slots:
    void login(QString,QString);
    void getMainwindowInfo(QString);


private slots:
    void loginReadySlots();
    void httpReadySlot();


signals:
    void sendLoginReplySignal(bool);
    void loginReady();
    void httpReady();

private:
    rest * pRest;
    QString loginResponse; //Token tai false
    QString httpResponse;
};


#endif // DLLRESTAPI_H
