#include "tilitapahtumawindow.h"
#include "qdebug.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "ui_tilitapahtumawindow.h"
#include <QTimer>
#include <QJsonArray>

TiliTapahtumaWindow::TiliTapahtumaWindow(QWidget *parent, QByteArray tiliData, bool credit) :     // Bool = credit
    QDialog(parent),
    ui(new Ui::TiliTapahtumaWindow)
{
    ui->setupUi(this);

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

/*    QList<QStandardItem> eventList;
    rivi rivi_1, rivi_2, rivi_3, rivi_4, rivi_5;
    eventList.append(&rivi_1);
    eventList.append(&rivi_2);
    eventList.append(&rivi_3);
    eventList.append(&rivi_4);
    eventList.append(&rivi_5);

    if (listaTesti) //tekee esimerkkilistan jos listaTesti = 1
    {

        rivi_1.setTime("1.4.2023");
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

    }
*/
    QJsonDocument doc = QJsonDocument::fromJson(tiliData);
    QJsonArray jsonArray = doc.array();
    //QList<QStandardItem> rivi;

    QStandardItemModel *taulukkoMalli = new QStandardItemModel(5,3,this);
    taulukkoMalli->setHeaderData(0, Qt::Horizontal, QObject::tr("Pvm"));
    taulukkoMalli->setHeaderData(1, Qt::Horizontal, QObject::tr("Tapahtuma"));
    taulukkoMalli->setHeaderData(2, Qt::Horizontal, QObject::tr("Maara"));



    for (int i = 0; i < 5; i++)
    {
        QJsonObject obj = jsonArray[i].toObject();
        QList<QStandardItem*> row;
        row << new QStandardItem(obj.value("pvm").toString());
        row << new QStandardItem(obj.value("TapahtumaNimi").toString());
        if (!credit)
        {
        row << new QStandardItem(QString::number(obj.value("SummaDebit").toDouble()));
        }
        else
        {
        row << new QStandardItem(QString::number(obj.value("SummaCredit").toDouble()));
        }
        taulukkoMalli->appendRow(row);
    }

    ui->tapahtumaTable->setModel(taulukkoMalli);
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
}

void TiliTapahtumaWindow::uudemmatButtonHandler()
{
    qDebug()<<"selataan tapahtumia";
    time=10;
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
