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
    delete ui;
    qDebug()<<"NaytaTapahtumaWindow tuhottu";
}

void NaytaTapahtumaWindow::setTapahtumaMaara(const QString &newTapahtumaMaara)
{
    tapahtumaMaara = newTapahtumaMaara;
}

void NaytaTapahtumaWindow::setTapahtumaNimi(const QString &newTapahtumaNimi)
{
    tapahtumaNimi = newTapahtumaNimi;
}

void NaytaTapahtumaWindow::setTapahtumaInfo(const QString &newTapahtumaInfo)
{
    tapahtumaInfo = newTapahtumaInfo;
}

void NaytaTapahtumaWindow::startTimer()
{
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));
}

void NaytaTapahtumaWindow::updateInfo()
{
    ui->maaraLabel->setText(tapahtumaMaara);
    ui->kohdeLabel->setText(tapahtumaNimi);
    ui->infoLabel->setText(tapahtumaInfo);

    // Timeri aloitetaan täällä eikä konstruktorissa, sillä tämä ikkuna
    // luodaan samaan aikaan kun valitseCharitySumma -ikkuna

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
