/****************************************
 * Näyttää tilitapahtumia 5 kerrallaan  *
 ****************************************/

#include "tilitapahtumawindow.h"
#include "qdebug.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "ui_tilitapahtumawindow.h"
#include <QTimer>
#include <QJsonArray>

TiliTapahtumaWindow::TiliTapahtumaWindow(QWidget *parent, QByteArray tiliData, bool credit) :
    QDialog(parent),
    ui(new Ui::TiliTapahtumaWindow)
{
    // normaaleja alustustoimenpiteitä
    ui->setupUi(this);
    identity=credit;
    pQTimer = new QTimer(this);
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));
    // yhdistetään napit handlereihin
    connect(ui->takaisinButton,SIGNAL(clicked(bool)),
            this,SLOT(takaisinButtonHandler()));
    connect(ui->uudetButton,SIGNAL(clicked(bool)),
            this,SLOT(uudemmatButtonHandler()));
    connect(ui->aiemmatButton,SIGNAL(clicked(bool)),
            this,SLOT(aiemmatButtonHandler()));

    //QList<rivi*> alkuIndeksi;   vanhaa legacykoodia
    /*rivi rivi_1, rivi_2, rivi_3, rivi_4, rivi_5;
    alkuIndeksi.append(&rivi_1);
    alkuIndeksi.append(&rivi_2);
    alkuIndeksi.append(&rivi_3);
    alkuIndeksi.append(&rivi_4);
    alkuIndeksi.append(&rivi_5);
    */
    // otetaan data vastaan ja siirretään JSONarray:in
    qDebug()<<"tilitapahtumat sai datan: "+tiliData;
    QJsonDocument doc = QJsonDocument::fromJson(tiliData);
    qDebug()<<doc;
    //jsonArray = doc.array();
    QJsonArray tempArray=doc.array();
    qDebug()<<"Arrayn sisällä on "<<jsonArray;


/*  vanhaa legacykoodia
    rivi_1.setTime(obj.value("pvm").toString());
    rivi_1.setEvent("Nosto");
    rivi_1.setMaara("100");
    rivi_2.setTime("3.4.2023");
    rivi_2.setEvent("Palkka");
    rivi_2.setMaara("500");
    rivi_3.setTime("4.4.2023");
    rivi_3.setEvent("Vesimaksu");
    rivi_3.setMaara("60");
    rivi_4.setTime("4.4.2023");
    rivi_4.setEvent("Kauppa");
    rivi_4.setMaara("150");
    rivi_5.setTime("6.4.2023");
    rivi_5.setEvent("Sudenpennut");
    rivi_5.setMaara("90");
*/

    // luodaan taulukko ja siihen 3 saraketta
    taulukkoMalli = new QStandardItemModel(0,3,this);
    taulukkoMalli->setHeaderData(0, Qt::Horizontal, QObject::tr("Pvm"));
    taulukkoMalli->setHeaderData(1, Qt::Horizontal, QObject::tr("Tapahtuma"));
    taulukkoMalli->setHeaderData(2, Qt::Horizontal, QObject::tr("Maara"));

    /****************************
     * Viedään data taulukkoon  *
     ****************************/

    for (; index < tempArray.size(); ++index)
    {

        QJsonObject obj = tempArray[index].toObject();
        qDebug()<<"kierros "<<index+1<<" ja objektin sisus: "<<obj;
        /****************************
         * jos datapiste on sopiva, *
         * viedään se taulukkoon    *
         ****************************/
        if ((!credit && obj.value("SummaDebit").toDouble() > 0) || (credit && obj.value("SummaCredit").toDouble()) > 0)
        {
            jsonArray.append(obj);
        }
    }
    updateTable();
    ui->tapahtumaTable->setModel(taulukkoMalli);
    ui->uudetButton->setEnabled(false); // alusta ei pääse uudempiin
    sivuMaara=(jsonArray.size()+4)/5;
    if (sivuMaara==1)
    {
        ui->aiemmatButton->setEnabled(false);   // jos datapisteet kaikki ovat jo taulukossa, disabloi nappi
    }

}

TiliTapahtumaWindow::~TiliTapahtumaWindow()
{
    delete ui;
    qDebug()<<"TiliTapahtumaWindow imploded";
}

void TiliTapahtumaWindow::takaisinButtonHandler()
{
    qDebug()<<"Takaisin";
    deleteLater();
}

void TiliTapahtumaWindow::aiemmatButtonHandler()
{
    qDebug()<<"selataan tapahtumia";
    time=10;
    sivu++;
    updateTable();
    // hallinnoidaan nappien toimivuutta
    if (sivu==sivuMaara-1)
    {
        ui->aiemmatButton->setEnabled(false);
    }
    ui->uudetButton->setEnabled(true);
}

void TiliTapahtumaWindow::uudemmatButtonHandler()
{
    qDebug()<<"selataan tapahtumia";
    time=10;
    sivu--;
    updateTable();
    // hallinnoidaan nappien toimivuutta
    ui->aiemmatButton->setEnabled(true);
    if (sivu==0)
        ui->uudetButton->setEnabled(false);
}

void TiliTapahtumaWindow::updateTimer()
{
    time--;
    qDebug()<<time;
    if(time == 0)
    {
        qDebug()<<"timeout";
        done(0);
        pQTimer->stop();
        deleteLater();
    }
}

void TiliTapahtumaWindow::updateTable()
{
    short alkuIndeksi=sivu*5;
    short loppuIndeksi=qMin(alkuIndeksi+5,jsonArray.size());
    taulukkoMalli->clear();
    for (; alkuIndeksi < loppuIndeksi; ++alkuIndeksi)
    {
        QJsonObject obj =jsonArray[alkuIndeksi].toObject();
        QList<QStandardItem*> alkuIndeksi;
        alkuIndeksi << new QStandardItem(obj.value("pvm").toString());
        alkuIndeksi << new QStandardItem(obj.value("TapahtumaNimi").toString());
        if (!identity)
        {
            alkuIndeksi << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
        }
        else
        {
            alkuIndeksi << new QStandardItem(QString::number(obj.value("SummaCredit").toDouble()));
        }
        taulukkoMalli->appendRow(alkuIndeksi);
    }
}
