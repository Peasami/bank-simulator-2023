#include "valitsesummawindow.h"
#include "ui_valitsesummawindow.h"
#include <QTimer>

ValitseSummaWindow::ValitseSummaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValitseSummaWindow)
{
    ui->setupUi(this);

    pQTimer = new QTimer(this);
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));

    setAttribute(Qt::WA_DeleteOnClose); // Olio tuhoutuu ruksia painaessa


    // Käy läpi kaikki napit
    for(int i=0;i<3;i++)
    {
        // Yhdistää kaikki nappien clicked signaalit yhteen buttonhandleriin
        connect(ui->leftSummaLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(summaButtonHandler()));
        connect(ui->rightSummaLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(summaButtonHandler()));
    }
}

ValitseSummaWindow::~ValitseSummaWindow()
{
    delete ui;
    qDebug()<<"valitseSummaWindow Tuhottu";
}

void ValitseSummaWindow::summaButtonHandler()
{
    // Hakee signaalin lähettäjän nimen, ja poistaa ensimmäisen kirjaimen
    QObject* buttonSender = sender();
    QString selectedSumma = buttonSender->objectName();
    selectedSumma.remove(0,1); // Poistetaan ensimmäinen kirjain


    if(selectedSumma.at(0).isLetter()) // Jos nappi on "valise muu summa" -nappi
    {
        qDebug()<<"isLetter";
        emit requestManualSumma();
        deleteLater();
    }
    else
    {
        qDebug()<<"isNumber";
        if(selectedSumma.toInt() > testiSaldo){
            qDebug()<<"Ei tarpeeksi saldoa!";
            done(0);            
            deleteLater();
        }
        testiSaldo -= selectedSumma.toInt();
        qDebug()<<"Nostit "<<selectedSumma<<"€. Saldosi: "<<testiSaldo;
        emit sendSumma(selectedSumma);
        deleteLater();
    }
    qDebug()<<selectedSumma;
}

void ValitseSummaWindow::updateTimer()
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
