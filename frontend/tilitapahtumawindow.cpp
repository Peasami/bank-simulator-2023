#include "tilitapahtumawindow.h"
#include "qdebug.h"
#include "ui_tilitapahtumawindow.h"
#include <QTimer>

TiliTapahtumaWindow::TiliTapahtumaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TiliTapahtumaWindow)
{
    ui->setupUi(this);

    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec

    connect(ui->takaisinButton,SIGNAL(clicked(bool)),
            this,SLOT(takaisinButtonHandler()));
    connect(ui->uudetButton,SIGNAL(clicked(bool)),
            this,SLOT(uudemmatButtonHandler()));
    connect(ui->aiemmatButton,SIGNAL(clicked(bool)),
            this,SLOT(aiemmatButtonHandler()));

    if (listaTesti) //tekee esimerkkilistan jos listaTesti = 1
    {
        QList<rivi*> eventList;
        rivi rivi_1, rivi_2, rivi_3, rivi_4, rivi_5;
        eventList.append(&rivi_1);
        eventList.append(&rivi_2);
        eventList.append(&rivi_3);
        eventList.append(&rivi_4);
        eventList.append(&rivi_5);

        rivi_1.setTime("1.4.2023");
        rivi_1.setEvent("Nosto");
        rivi_1.setMaara("100");
        rivi_1.setSaldo("30");
        rivi_2.setTime("3.4.2023");
        rivi_2.setEvent("Palkka");
        rivi_2.setMaara("500");
        rivi_2.setSaldo("530");
        rivi_3.setTime("4.4.2023");
        rivi_3.setEvent("Vesimaksu");
        rivi_3.setMaara("60");
        rivi_3.setSaldo("470");
        rivi_4.setTime("4.4.2023");
        rivi_4.setEvent("Kauppa");
        rivi_4.setMaara("150");
        rivi_4.setSaldo("320");
        rivi_5.setTime("6.4.2023");
        rivi_5.setEvent("Sudenpennut");
        rivi_5.setMaara("90");
        rivi_5.setSaldo("230");

        QStandardItemModel *table_model = new QStandardItemModel(eventList.size(),4);
        table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Pvm"));
        table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Tapahtuma"));
        table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Maara"));
        table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Tilin Saldo"));

        for (int row = 0; row < eventList.size(); ++row) {
            QStandardItem *pTime = new QStandardItem((eventList[row]->getTime()));
            table_model->setItem(row, 0, pTime);
            QStandardItem *pEvent = new QStandardItem((eventList[row]->getEvent()));
            table_model->setItem(row, 1, pEvent);
            QStandardItem *pMaara = new QStandardItem((eventList[row]->getMaara()));
            table_model->setItem(row, 2, pMaara);
            QStandardItem *pSaldo = new QStandardItem((eventList[row]->getSaldo()));
            table_model->setItem(row, 3, pSaldo);
        }

        ui->tapahtumaTable->setModel(table_model);
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
