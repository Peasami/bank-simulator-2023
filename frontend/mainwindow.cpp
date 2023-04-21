#include "mainwindow.h"
#include "insertcardwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RestApi = new DLLRestAPI(this);

    SetUserName("Santeri");
    IsCredit(false);

    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec

    connect(pQTimer, SIGNAL(timeout()),
            this,SLOT(mainTimer()));

    connect(qApp, &QApplication::focusChanged,
            this,&MainWindow::applicationFocusChanged);

    pSaldo = new saldoWindow(this);
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

    pTiliTapahtuma = new TiliTapahtumaWindow(this);
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
        ui->tiliLabel->setText("Credit");
    }
    else{
        ui->tiliLabel->setText("Debit");
    }
}

void MainWindow::disableVaihdaBtn()
{
    ui->vaihdaTiliButton->setDisabled(true);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saldoButton_handler()
{
    qDebug()<<"saldo";
    pSaldo->open();
    //QString cardNum = "06000d8977"; //testi joka hakee tuolla kortilla sen saldon

    //RestApi->getSaldoInfo(cardNum);
}

void MainWindow::vaihdaTiliButton_handler()
{
    pVaihdaTilia = new VaihdaTiliaWindow(this);
    connect(pVaihdaTilia,SIGNAL(sendIsCredit(bool)),
            this,SLOT(receiveIsCredit(bool)));
    connect(pVaihdaTilia,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));

    qDebug()<<"vaihda tiliä";
    pVaihdaTilia->open();
}

void MainWindow::lopetaButton_handler()
{
    qDebug()<<"Hei lopeta!";
    InsertCardWindow W;


}

void MainWindow::lahjoitaButton_handler()
{
    pLahjoitaRahaa = new LahjoitaRahaaWindow(this);
    connect(pLahjoitaRahaa,SIGNAL(sendCharity(QString)),
            this,SLOT(receiveCharity(QString)));
    connect(pLahjoitaRahaa,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));

    qDebug()<<"lahjoita";
    pLahjoitaRahaa->open();

    // Tehdään olio näytäTapahtumasta, jotta sinne saadaan
    // lahjoituksen kohde ja määrä talteen muuttujiin
    pNaytaTapahtuma = new NaytaTapahtumaWindow(this);
}

void MainWindow::nostaRahaaButton_handler()
{
    pValitseSumma = new ValitseSummaWindow(this);
    connect(pValitseSumma,SIGNAL(sendSumma(QString)), // ValitseSummaWindow lähettää sendSumma -signaalin, joka yhdistetään receiveNostoon
            this,SLOT(receiveNostoSumma(QString)));

    connect(pValitseSumma,SIGNAL(requestManualSumma()),
            this,SLOT(openManualNostoSumma()));
    connect(pValitseSumma,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));
    pValitseSumma->open();
    qDebug()<<"nosta rahaa";
}

void MainWindow::tilitapahtumatButton_handler()
{
    //QString cardNum = "06000d8977";   //testi, joka hakee tuolla kortinnumerolla sen tilitapahtumat
    //RestApi->getAccountHistoryInfo(cardNum);
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
    // kun saadaan lahjoituskohde, tehdään olio ja aukaistaan ikkuna jossa valitaan lahjoituksen määrä
    pValitseSumma = new ValitseSummaWindow(this);
    connect(pValitseSumma,SIGNAL(sendSumma(QString)), // ValitseSumman sendSumma signaali yhdistetään receiveCharitySummaan
            this,SLOT(receiveCharitySumma(QString)));

    connect(pValitseSumma,SIGNAL(requestManualSumma()),
            this,SLOT(openManualCharitySumma()));
    connect(pValitseSumma,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));

    pValitseSumma->open();

    // Annetaan kohteen nimi näytäTapahtumalle
    pNaytaTapahtuma->setLahjoitusKohde(charity);
    qDebug()<<"recieveCharity(): "<<charity;
}

void MainWindow::receiveCharitySumma(QString charitySumma)
{
    qDebug()<<"receiveCharitySumma(): "<<charitySumma;

    // Annetaan lahjoituksen määrä näytäTapahtumalle
    pNaytaTapahtuma->setLahjoitusMaara(charitySumma);

    // päivitetään ui ja näytetään
    pNaytaTapahtuma->updateInfo();
    pNaytaTapahtuma->show();
}

void MainWindow::receiveNostoSumma(QString nostoSumma)
{
    qDebug()<<"receiveNostoSumma(): "<<nostoSumma;
}

void MainWindow::printSaldoDataSlot()
{
    qDebug() << "getSaldo called";
    QByteArray saldoData = RestApi->getHttpResponse();
    qDebug() << "exe vastaan otti datan, joka on: " <<saldoData;


}

void MainWindow::printAccountHistoryDataSlot()

{

    qDebug() << "getAccount called";
    QByteArray accountHistoryData = RestApi->getHttpResponse();

    qDebug() << "exe vastaan otti datan, joka on: " << accountHistoryData;

    accountHistoryData.clear();
}



void MainWindow::openManualCharitySumma()
{
    qDebug()<<"openManualCharitySumma()";

    // Tehdään ja avataan ManualSummaWindow, yhdistetään summan lähetys receive*CHARITY*Summaan
    pManualSumma = new ManualSummaWindow(this);
    connect(pManualSumma,SIGNAL(sendSumma(QString)),
            this,SLOT(receiveCharitySumma(QString)));
    connect(pManualSumma,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));
    pManualSumma->open();
}

void MainWindow::openManualNostoSumma()
{
    qDebug()<<"openManualNostoSumma()";

    // Tehdään ja avataan ManualSummaWindow, yhdistetään summan lähetys receive*NOSTO*Summaan
    pManualSumma = new ManualSummaWindow(this);
    connect(pManualSumma,SIGNAL(sendSumma(QString)),
            this,SLOT(receiveNostoSumma(QString)));
    connect(pManualSumma,SIGNAL(deleteWindow(QWidget*)),
            this, SLOT(deleteWindowSlot(QWidget*)));
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



void MainWindow::deleteWindowSlot(QWidget * pWindow)
{
    delete pWindow;
    pWindow = nullptr;
}

