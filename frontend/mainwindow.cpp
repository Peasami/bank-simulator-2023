#include "mainwindow.h"
#include "insertcardwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent, QString cardNum, DLLRestAPI *pointer)//, QByteArray token1)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //token = token1;
    //RestApi = new DLLRestAPI(this);
    RestApi = pointer;

    connect(this,SIGNAL(cardType(QString)),
            RestApi,SLOT(getTilityyppi(QString)));




    SetUserName("Santeri");
    IsCredit(false);
    cardNumber = cardNum;
    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec

    connect(pQTimer, SIGNAL(timeout()),
            this,SLOT(mainTimer()));

    connect(qApp, &QApplication::focusChanged,
            this,&MainWindow::applicationFocusChanged);


    connect(ui->saldoButton,SIGNAL(clicked(bool)),
            this,SLOT(saldoButton_handler()));

    connect(ui->lahjoitaButton,SIGNAL(clicked(bool)),
            this,SLOT(lahjoitaButton_handler()));

    connect(ui->vaihdaTiliButton,SIGNAL(clicked(bool)),
            this,SLOT(vaihdaTiliButton_handler()));

    connect(ui->lopetaButton,SIGNAL(clicked(bool)),
            this,SLOT(lopetaButton_handler()));

    connect(ui->nostaRahaaButton,SIGNAL(clicked(bool)),
            this,SLOT(nostaRahaaButton_handler()));

    connect(ui->tilitapahtumatButton,SIGNAL(clicked(bool)),
            this,SLOT(tilitapahtumatButton_handler()));


}

void MainWindow::SetUserName(QString name)
{
    ui->tiliNimiLabel->setText(name);
}

void MainWindow::IsCredit(bool isCredit)
{
    if(isCredit == true){
        credit=1;
        ui->tiliLabel->setText("Credit");
        emit cardType("Credit");
    }
    else{
        credit=0;
        ui->tiliLabel->setText("Debit");
        emit cardType("Debit");
    }
}

void MainWindow::disableVaihdaBtn()
{
    ui->vaihdaTiliButton->setDisabled(true);
}



MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"MainWindow tuhottiin";
    emit loggedOut(true);
}


void MainWindow::saldoButton_handler()
{
    pSaldo = new saldoWindow(this,credit);
    connect(RestApi, SIGNAL(getSaldoSignal()),
            this,SLOT(printSaldoDataSlot()));

    qDebug()<<"saldo";
    pSaldo->open();
    //QString cardNum = "06000d8977"; //testi joka hakee tuolla kortilla sen saldon
    qDebug()<<" saldobuttonin  mainwindowissa kortinnumero on "+cardNumber;
    RestApi->getSaldoInfo(cardNumber);

}

void MainWindow::vaihdaTiliButton_handler()
{
    pVaihdaTilia = new VaihdaTiliaWindow(this);
    connect(pVaihdaTilia,SIGNAL(sendIsCredit(bool)),
            this,SLOT(receiveIsCredit(bool)));

    qDebug()<<"vaihda tiliä";
    pVaihdaTilia->open();
}

void MainWindow::lopetaButton_handler()
{
    qDebug()<<"Hei lopeta!";
    //InsertCardWindow W;
    deleteLater();


}

void MainWindow::lahjoitaButton_handler()
{
    pLahjoitaRahaa = new LahjoitaRahaaWindow(this);
    connect(pLahjoitaRahaa,SIGNAL(sendCharity(QString)),
            this,SLOT(receiveCharity(QString)));


    qDebug()<<"lahjoita";
    pLahjoitaRahaa->open();

    // Tehdään olio näytäTapahtumaWindowista, jotta sinne saadaan
    // lahjoituksen kohde ja määrä talteen muuttujiin.
    // Timeriä tähän ikkunaan ei alusteta konstruktorissa
    pNaytaTapahtuma = new NaytaTapahtumaWindow(this);


}

void MainWindow::nostaRahaaButton_handler()
{
    pValitseSumma = new ValitseSummaWindow(this);
    connect(pValitseSumma,SIGNAL(sendSumma(QString)), // ValitseSummaWindow lähettää sendSumma -signaalin, joka yhdistetään receiveNostoon
            this,SLOT(receiveNostoSumma(QString)));

    connect(pValitseSumma,SIGNAL(requestManualSumma()),
            this,SLOT(openManualNostoSumma()));
    pValitseSumma->open();
    connect(this,SIGNAL(sendTransfer(QString,int)),
            RestApi,SLOT(receiveTransfer(QString,int)));

    qDebug()<<"nosta rahaa";

}

void MainWindow::tilitapahtumatButton_handler()
{

    connect(RestApi, SIGNAL(accountHistorySignal()),
            this,SLOT(printAccountHistoryDataSlot()));
    RestApi->getAccountHistoryInfo(cardNumber);
    pTiliTapahtuma = new TiliTapahtumaWindow(this,accountHistoryData,credit);
    //QString cardNum = "06000d8977";   // testi, joka hakee tuolla kortinnumerolla sen tilitapahtumat
    //,token);
    qDebug()<<"tilitapahtumat";
    pTiliTapahtuma->open();
}


void MainWindow::receiveIsCredit(bool b)
{
    qDebug()<<"recieveIsCredit";
    IsCredit(b);
}

void MainWindow::receiveCharity(QString charity)
{
    targetCharity = charity; // Asetetaan privaattimuuttuja, jotta tieto voidaan lähettää backendiin

    // kun saadaan lahjoituskohde, tehdään olio ja aukaistaan ikkuna jossa valitaan lahjoituksen määrä
    pValitseSumma = new ValitseSummaWindow(this);
    connect(pValitseSumma,SIGNAL(sendSumma(QString)), // ValitseSumman sendSumma signaali yhdistetään receiveCharitySummaan
            this,SLOT(receiveCharitySumma(QString)));

    connect(pValitseSumma,SIGNAL(requestManualSumma()),
            this,SLOT(openManualCharitySumma()));

    pValitseSumma->open();

    // Annetaan kohteen nimi näytäTapahtumalle
    pNaytaTapahtuma->setTapahtumaNimi(charity+" kiittää!");
    pNaytaTapahtuma->setTapahtumaInfo("Kiitos lahjoituksesta!");

    connect(this,SIGNAL(CharityTransfer(QString,int)),
              RestApi,SLOT(receiveTransfer(QString,int)));



    qDebug()<<"recieveCharity(): "<<charity;
}

// Kun lahjoitettava summa on valittu toisesta ikkunasta, palataan tähän funktioon
void MainWindow::receiveCharitySumma(QString charitySumma)
{
    qDebug()<<"receiveCharitySumma(): "<<charitySumma;

    // Annetaan lahjoituksen määrä näytäTapahtumalle
    pNaytaTapahtuma->setTapahtumaMaara(charitySumma+"€");



    // päivitetään ui ja näytetään
    pNaytaTapahtuma->updateInfo();

    // Lähetetään DLLRestApille transfer -tapahtuman nimi ja määrä
    emit CharityTransfer("lahjoitus, "+targetCharity, charitySumma.toInt());
    disconnect(this,SIGNAL(CharityTransfer(QString,int)),
               RestApi,SLOT(receiveTransfer(QString,int)));

    // Kun DLLRestApi lähettää signaalin, saa tiedon oliko tilillä saldoa vai ei
    connect(RestApi, SIGNAL(updateSaldoSignal()),
            this, SLOT(receiveTransferDataSlot()));

    // DLLRestApiin kortin numero talteen
    RestApi->updateSaldoInfo(cardNumber);



}

void MainWindow::receiveNostoSumma(QString nostoSumma)
{
    // Lähettää DLLRestApille pyynnön nostosta, ja disconnectaa signaalin
    emit sendTransfer("nosto",nostoSumma.toInt());

    disconnect(this,SIGNAL(sendTransfer(QString,int)),
               RestApi,SLOT(receiveTransfer(QString,int)));

    connect(RestApi, SIGNAL(updateSaldoSignal()),
            this, SLOT(receiveTransferDataSlot()));


    RestApi->updateSaldoInfo(cardNumber);


    qDebug()<<"receiveNostoSumma(): "<<nostoSumma;

    pNaytaTapahtuma = new NaytaTapahtumaWindow(this);
    qDebug()<<"In ReceiveNostoSumma(), saldoData Näyttää: "<<saldoData;
    pNaytaTapahtuma->setTapahtumaMaara(nostoSumma+"€");
    pNaytaTapahtuma->setTapahtumaNimi("");
    pNaytaTapahtuma->setTapahtumaInfo("Nostettu: ");
    pNaytaTapahtuma->updateInfo();
}

void MainWindow::printSaldoDataSlot()
{
    disconnect(RestApi, SIGNAL(getSaldoSignal()),
            this,SLOT(printSaldoDataSlot()));
    saldoData = RestApi->getHttpResponse();
    qDebug() << "printSaldoDataSlot exessä vastaan otti datan, joka on:" <<saldoData;


}


void MainWindow::printAccountHistoryDataSlot()

{
    disconnect(RestApi, SIGNAL(accountHistorySignal()),
            this,SLOT(printAccountHistoryDataSlot()));


    accountHistoryData = RestApi->getHttpResponse();

    qDebug() << "exe vastaan otti datan, joka on: " << accountHistoryData;

    //accountHistoryData.clear();
}

// Hakee tiedon oliko tilillä saldoa transferiin vai ei
void MainWindow::receiveTransferDataSlot()
{
    QByteArray TransferData = RestApi->getHttpResponse();
    disconnect(RestApi,SIGNAL(updateSaldoSignal()),
               this,SLOT(receiveTransferDataSlot()));
    qDebug()<< "receiveTransferDataSlot exessä vastaan otti datan,joka on: "<<TransferData;

    // Jos tilillä on saldoa, TransferData == 1, muuten 0
    if(TransferData.toInt() == 1){          // Näytetään ikkuna ja aloitetaan timeri
        qDebug()<<"TransferData == 1";
        pNaytaTapahtuma->startTimer();
        pNaytaTapahtuma->show();
    }
    else{                                   // NaytaTapahtuma tyhjennetään ja kerrotaan "ei saldoa"
        qDebug()<<"TransferData != 1";
        pNaytaTapahtuma->setTapahtumaNimi("EI SALDOA");
        pNaytaTapahtuma->setTapahtumaInfo("");
        pNaytaTapahtuma->setTapahtumaMaara("");
        pNaytaTapahtuma->updateInfo();
        pNaytaTapahtuma->startTimer();
        pNaytaTapahtuma->show();
    }
}

void MainWindow::TransactionDone()
{
    deleteLater();
}





void MainWindow::openManualCharitySumma()
{
    qDebug()<<"openManualCharitySumma()";

    // Tehdään ja avataan ManualSummaWindow, yhdistetään summan lähetys receive*CHARITY*Summaan
    pManualSumma = new ManualSummaWindow(this);
    connect(pManualSumma,SIGNAL(sendSumma(QString)),
            this,SLOT(receiveCharitySumma(QString)));
    pManualSumma->open();
}

void MainWindow::openManualNostoSumma()
{
    qDebug()<<"openManualNostoSumma()";

    // Tehdään ja avataan ManualSummaWindow, yhdistetään summan lähetys receive*NOSTO*Summaan
    pManualSumma = new ManualSummaWindow(this);
    connect(pManualSumma,SIGNAL(sendSumma(QString)),
            this,SLOT(receiveNostoSumma(QString)));
    pManualSumma->open();
}

void MainWindow::mainTimer()
{
    mainTime--;
    qDebug()<<mainTime;

    if(mainTime == 0)
    {
        qDebug()<<"mainin timeout";
        pQTimer->stop();
        deleteLater();
    }
}

void MainWindow::applicationFocusChanged(QWidget *oldWidget, QWidget *newWidget)
{
    if(!oldWidget)
    {
        pQTimer->start();
    }
    else if(newWidget)
    {
        pQTimer->stop();
        mainTime=30;
    }
}
