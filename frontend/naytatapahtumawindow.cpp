#include "naytatapahtumawindow.h"
#include "ui_naytatapahtumawindow.h"
#include <QTimer>

NaytaTapahtumaWindow::NaytaTapahtumaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NaytaTapahtumaWindow)
{
    ui->setupUi(this);
    pQTimer = new QTimer(this);
    qDebug()<<"NaytaTapahtumaWindow luotu";
}

NaytaTapahtumaWindow::~NaytaTapahtumaWindow()
{
    emit endSession();
    delete ui;
    qDebug()<<"NaytaTapahtumaWindow tuhottu";
}

void NaytaTapahtumaWindow::setLahjoitusMaara(const QString &newLahjoitusMaara)
{
    lahjoitusMaara = newLahjoitusMaara;
}

void NaytaTapahtumaWindow::setLahjoitusKohde(const QString &newLahjoitusKohde)
{
    lahjoitusKohde = newLahjoitusKohde;
}

void NaytaTapahtumaWindow::updateInfo()
{
    ui->maaraLabel->setText(lahjoitusMaara);
    ui->kohdeLabel->setText(lahjoitusKohde);

    // Timeri aloitetaan täällä eikä konstruktorissa, sillä tämä ikkuna
    // luodaan samaan aikaan kun valitseCharitySumma -ikkuna
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));
}
void NaytaTapahtumaWindow::updateTimer()
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
