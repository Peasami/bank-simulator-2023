#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saldowindow.h"
#include "tilitapahtumawindow.h"
#include "vaihdatiliawindow.h"
#include "lahjoitarahaawindow.h"
#include "valitsesummawindow.h"
#include "naytatapahtumawindow.h"
#include "manualsummawindow.h"
#include "dllrestapi.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QString cardNum = "",DLLRestAPI *pointer=nullptr);//, QByteArray token1 = "");
    void SetUserName(QString);
    void IsCredit(bool);
    void disableVaihdaBtn();
    ~MainWindow();

signals:
    void loggedOut(bool);

private slots:
    void saldoButton_handler();
    void vaihdaTiliButton_handler();
    void lopetaButton_handler();
    void lahjoitaButton_handler();
    void nostaRahaaButton_handler();
    void tilitapahtumatButton_handler();

    void receiveIsCredit(bool);
    void receiveCharity(QString);
    void receiveCharitySumma(QString);
    void receiveNostoSumma(QString);

    void printSaldoDataSlot();
    void printAccountHistoryDataSlot();
    void receiveTransferDataSlot();

    void openManualCharitySumma();
    void openManualNostoSumma();

    void deleteWindowSlot(QWidget *);
private:
    Ui::MainWindow *ui;
    VaihdaTiliaWindow * pVaihdaTilia;
    LahjoitaRahaaWindow * pLahjoitaRahaa;
    ValitseSummaWindow * pValitseSumma;
    NaytaTapahtumaWindow * pNaytaTapahtuma;
    ManualSummaWindow * pManualSumma;
    saldoWindow * pSaldo;
    TiliTapahtumaWindow * pTiliTapahtuma;
    DLLRestAPI * RestApi;
    QString cardNumber;
    QByteArray token;
signals:

    void sendTransfer(QString, int);
    void CharityTransfer(QString,int);
    void cardType(QString);



};
#endif // MAINWINDOW_H
