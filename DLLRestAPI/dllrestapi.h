
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

    const QByteArray &getHttpResponse() const;

    const QByteArray &getSaldoResponse() const;
    void setSaldoResponse(const QByteArray &newSaldoResponse);

public slots:
    void login(QString,QString);
    void getMainwindowInfo(QString);
    void getAccountHistoryInfo(QString);
    void getSaldoInfo(QString);

private slots:
    void loginReadySlots();
    void httpReadySlot();
    void accountHistorySlot();
    void getSaldoSlot();

signals:
    void sendLoginReplySignal(bool);
    void loginReady();
    void httpReady();
    void accountHistorySignal();
    void getSaldoSignal();

private:
    rest * pRest;
    QString loginResponse; //Token tai false
    QByteArray httpResponse;
    QByteArray SaldoResponse;
};


#endif // DLLRESTAPI_H
