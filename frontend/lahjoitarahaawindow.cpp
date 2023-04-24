#include "lahjoitarahaawindow.h"
#include "ui_lahjoitarahaawindow.h"
#include <QDebug>
#include <QTimer>

LahjoitaRahaaWindow::LahjoitaRahaaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LahjoitaRahaaWindow)
{
    ui->setupUi(this);
    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec

    // Käy läpi kaikki windowin napit
    for(int i=0;i<3;i++)
    {
        // Yhdistää kaikki nappien clicked signaalit yhteen buttonhandleriin
        connect(ui->leftCharitiesLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(charityButtonHandler()));
        connect(ui->rightCharitiesLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(charityButtonHandler()));


        // Lisää nappien nimet charityList listaan
        charityList.append(ui->leftCharitiesLayout->itemAt(i)->widget()->objectName());
        charityList.append(ui->rightCharitiesLayout->itemAt(i)->widget()->objectName());

    }
}

LahjoitaRahaaWindow::~LahjoitaRahaaWindow()
{
    delete ui;
    qDebug()<<"LahjoitaRahaaWindow tuhottu";
}

void LahjoitaRahaaWindow::charityButtonHandler()
{
    // Otetaan talteen signaalin lähettäjä ja lähettäjän nimi
    QObject* buttonSender = sender();
    selectedCharity = buttonSender->objectName();

    if(selectedCharity == "takaisinButton"){
        qDebug()<<"selectedCharity == takaisinButton";
        //emit deleteWindow(this);
        deleteLater();
    }
    else
    {
        time = 10;
        ///emit sendCharity(selectedCharity);

        //etsii charityList -listasta napin nimeä vastaavan indeksin, jotta voidaan käyttää switch casea
        switch(charityList.indexOf(buttonSender->objectName()))
        {
        case 0:
            emit sendCharity("Pelastakaa Lapset");
            break;
        case 1:
            emit sendCharity("Syöpäsäätiö");
            break;
        case 2:
            emit sendCharity("Punainen Risti");
            break;
        case 3:
            emit sendCharity("Mieli RY");
            break;
        case 4:
            emit sendCharity("Pelastusarmeija");
            break;
        }

        deleteLater();
    }
}

void LahjoitaRahaaWindow::updateTimer()
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
