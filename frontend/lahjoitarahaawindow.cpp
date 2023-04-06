#include "lahjoitarahaawindow.h"
#include "ui_lahjoitarahaawindow.h"
#include <QDebug>

LahjoitaRahaaWindow::LahjoitaRahaaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LahjoitaRahaaWindow)
{
    ui->setupUi(this);

    // Käy läpi kaikki windowin napit
    for(int i=0;i<3;i++)
    {
        // Yhdistää kaikki nappien clicked signaalit yhteen buttonhandleriin
        connect(ui->leftCharitiesLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(charityButtonHandler()));
        connect(ui->rightCharitiesLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(charityButtonHandler()));


        ///// Lisää nappien nimet charityList listaan
        ///charityList.append(ui->leftCharitiesLayout->itemAt(i)->widget()->objectName());
        ///charityList.append(ui->rightCharitiesLayout->itemAt(i)->widget()->objectName());

    }
}

LahjoitaRahaaWindow::~LahjoitaRahaaWindow()
{
    delete ui;
}

void LahjoitaRahaaWindow::charityButtonHandler()
{
    // Otetaan talteen signaalin lähettäjä ja lähettäjän nimi
    QObject* buttonSender = sender();
    selectedCharity = buttonSender->objectName();

    if(selectedCharity == "takaisinButton"){
        done(0);
        qDebug()<<"selectedCharity == takaisinButton";
        return;
    }
    emit sendCharity(selectedCharity);
    done(0);


    /** //etsii charityList -listasta napin nimeä vastaavan indeksin, jotta voidaan käyttää switch casea
    switch(charityList.indexOf(buttonSender->objectName()))
    {
    case 0:
        qDebug()<<"pelastakaalapset";
        break;

    case 1:
        qDebug()<<"syöpäsäätiö";
        break;
    }
    */
}
