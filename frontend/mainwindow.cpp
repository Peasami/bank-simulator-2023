#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetUserName("Santeri");
    IsCredit(false);

    pVaihdaTilia = new VaihdaTiliaWindow(this);
    connect(pVaihdaTilia,SIGNAL(sendIsCredit(bool)),
            this,SLOT(receiveIsCredit(bool)));

    pLahjoitaRahaa = new LahjoitaRahaaWindow(this);
    connect(pLahjoitaRahaa,SIGNAL(sendCharity(QString)),
            this,SLOT(receiveCharity(QString)));

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
        ui->tiliLabel->setText("Credit");
    }
    else{
        ui->tiliLabel->setText("Debit");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::saldoButton_handler()
{
    qDebug()<<"saldo";
}

void MainWindow::vaihdaTiliButton_handler()
{
    qDebug()<<"vaihda tiliä";
    pVaihdaTilia->open();
}

void MainWindow::lopetaButton_handler()
{
    qDebug()<<"lopeta";
}

void MainWindow::lahjoitaButton_handler()
{
    qDebug()<<"lahjoita";
    pLahjoitaRahaa->open();

    // Tehdään olio näytäTapahtumasta, jotta sinne saadaan lahjoituksen kohde ja määrä talteen muuttujiin
    pNaytaTapahtuma = new NaytaTapahtumaWindow(this);
}

void MainWindow::nostaRahaaButton_handler()
{
    qDebug()<<"nosta rahaa";
}

void MainWindow::tilitapahtumatButton_handler()
{
    qDebug()<<"tilitapahtumat";
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
    connect(pValitseSumma,SIGNAL(sendSumma(QString)),
            this,SLOT(receiveCharitySumma(QString)));
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

