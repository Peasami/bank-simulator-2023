#include "naytatapahtumawindow.h"
#include "ui_naytatapahtumawindow.h"

NaytaTapahtumaWindow::NaytaTapahtumaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NaytaTapahtumaWindow)
{
    ui->setupUi(this);
}

NaytaTapahtumaWindow::~NaytaTapahtumaWindow()
{
    delete ui;
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
}
