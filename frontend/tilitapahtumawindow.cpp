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
    ui->setupUi(this);
    identity=credit;
    pQTimer = new QTimer(this);
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));

    connect(ui->takaisinButton,SIGNAL(clicked(bool)),
            this,SLOT(takaisinButtonHandler()));
    connect(ui->uudetButton,SIGNAL(clicked(bool)),
            this,SLOT(uudemmatButtonHandler()));
    connect(ui->aiemmatButton,SIGNAL(clicked(bool)),
            this,SLOT(aiemmatButtonHandler()));

    //QList<rivi*> eventList;
    /*rivi rivi_1, rivi_2, rivi_3, rivi_4, rivi_5;
    eventList.append(&rivi_1);
    eventList.append(&rivi_2);
    eventList.append(&rivi_3);
    eventList.append(&rivi_4);
    eventList.append(&rivi_5);
    */

    qDebug()<<"tilitapahtumat sai datan: "+tiliData;
    QJsonDocument doc = QJsonDocument::fromJson(tiliData);
    qDebug()<<doc;
    jsonArray = doc.array();
    qDebug()<<"Arrayn sisällä on "<<jsonArray;


/*
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
    taulukkoMalli = new QStandardItemModel(0,3,this);
    taulukkoMalli->setHeaderData(0, Qt::Horizontal, QObject::tr("Pvm"));
    taulukkoMalli->setHeaderData(1, Qt::Horizontal, QObject::tr("Tapahtuma"));
    taulukkoMalli->setHeaderData(2, Qt::Horizontal, QObject::tr("Maara"));


    //insertItem(int index, QListWidgetItem *item)        void	insertRow(int index, const QList<QStandardItem *> &items)

    short kierros=0;
    for (; eventList < jsonArray.size()&&kierros<5; ++eventList) {

        QJsonObject obj = jsonArray[eventList].toObject();
        qDebug()<<"kierros "<<eventList+1<<" ja objektin sisus: "<<obj;
        if ((!credit && obj.value("SummaDebit").toDouble() > 0) || (credit && obj.value("SummaCredit").toDouble() > 0))
        {

            QList<QStandardItem*> eventList;
            eventList << new QStandardItem(obj.value("pvm").toString());
            eventList << new QStandardItem(obj.value("TapahtumaNimi").toString());
            if (!credit)
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
            }
            else
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
            }

            taulukkoMalli->appendRow(eventList);
            kierros++;
        }
        //index++;

    }

    ui->tapahtumaTable->setModel(taulukkoMalli);
    ui->uudetButton->setEnabled(false);
    if (eventList+1>=jsonArray.size())
    {
        ui->aiemmatButton->setEnabled(false);
    }
    //ui->;
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
    edellinenSivu=sivu;
    sivu=eventList;
    short kierros=0;
    for (;eventList < jsonArray.size()&&kierros<5; ++eventList) {
        QJsonObject obj = jsonArray[eventList].toObject();
        qDebug()<<"kierros "<<eventList+1<<" ja objektin sisus: "<<obj;
        if ((!identity && obj.value("SummaDebit").toDouble() > 0) || (identity && obj.value("SummaCredit").toDouble() > 0))
        {
            QList<QStandardItem*> eventList;
            eventList << new QStandardItem(obj.value("pvm").toString());
            eventList << new QStandardItem(obj.value("TapahtumaNimi").toString());
            if (!identity)
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
            }
            else
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaCredit").toDouble()));
            }
            taulukkoMalli->insertRow(kierros,eventList);
            kierros++;
        }

    }
    taulukkoMalli->setRowCount(kierros);
    if (eventList+1>=jsonArray.size())
    {
        ui->aiemmatButton->setEnabled(false);
    }
    ui->uudetButton->setEnabled(true);

}

void TiliTapahtumaWindow::uudemmatButtonHandler()
{
    qDebug()<<"selataan tapahtumia";
    time=10;
    eventList=edellinenSivu;
    sivu=edellinenSivu;
    edellinenSivu=0;
    short kierros=0;
    taulukkoMalli->setRowCount(5);
    /*if (taulukkoMalli->rowCount()<5)
    {
        for (kierros = taulukkoMalli->rowCount(); kierros < 5; ++kierros)
        {
            QList<QStandardItem*> kierros;
            taulukkoMalli->appendRow(kierros);
        }
    }*/

    //kierros=0;
    for (;eventList < jsonArray.size()&&kierros<5; ++eventList) {
        QJsonObject obj = jsonArray[eventList].toObject();
        qDebug()<<"kierros "<<eventList+1<<" ja objektin sisus: "<<obj;
        if ((!identity && obj.value("SummaDebit").toDouble() > 0) || (identity && obj.value("SummaCredit").toDouble() > 0))
        {
            eventList++;
            QList<QStandardItem*> eventList;
            eventList << new QStandardItem(obj.value("pvm").toString());
            eventList << new QStandardItem(obj.value("TapahtumaNimi").toString());
            if (!identity)
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
            }
            else
            {
                eventList << new QStandardItem(QString::number(obj.value("SummaCredit").toDouble()));
            }
            taulukkoMalli->insertRow(kierros,eventList);
            kierros++;
        }

    }
    ui->aiemmatButton->setEnabled(true);
    if (sivu==0)
    {
        ui->uudetButton->setEnabled(false);
        eventList=0;
    }
    taulukkoMalli->setRowCount(5);

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
