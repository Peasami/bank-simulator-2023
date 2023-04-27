
#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H
#include <QDebug>
#include <QObject>
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
    void checkBlacklist(QString);
    void addToBlacklist(QString);


public slots:
    void login(QString,QString);
    void getMainwindowInfo(QString);
    void getAccountHistoryInfo(QString);//,QByteArray);
    void getSaldoInfo(QString);
    void updateSaldoInfo(QString);
    void getTilityyppi(QString);
    void receiveTransfer(QString, int);


private slots:
    void loginReadySlots();
    void httpReadySlot();
    void accountHistorySlot();
    void getSaldoSlot();
    void updateSaldoSlot();
    void blacklistSlot();
    //void updateBlacklistSlot();

signals:
    void sendLoginReplySignal(bool);
    void loginReady();
    void httpReady();
    void accountHistorySignal();
    void getSaldoSignal();
    void updateSaldoSignal();
    void blacklistSignal();
    //void updateBlacklistSignal();
private:
    rest * pRest;
    QString loginResponse; //Token tai false
    QByteArray httpResponse;
    QString tilityyppi;
    QString tapahtumaNimi;



};


#endif // DLLRESTAPI_H
