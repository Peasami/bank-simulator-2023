#include "naytatapahtumawindow.h"
#include "ui_naytatapahtumawindow.h"
#include <QTimer>

NaytaTapahtumaWindow::NaytaTapahtumaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NaytaTapahtumaWindow)
{
    ui->setupUi(this);
    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec
}

NaytaTapahtumaWindow::~NaytaTapahtumaWindow()
{
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
    lahjoitusKohde.remove("Button");
}

void NaytaTapahtumaWindow::updateInfo()
{
    ui->maaraLabel->setText(lahjoitusMaara);
    ui->kohdeLabel->setText(lahjoitusKohde);
}
