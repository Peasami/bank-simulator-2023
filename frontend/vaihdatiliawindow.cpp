#include "vaihdatiliawindow.h"
#include "qtimer.h"
#include "ui_vaihdatiliawindow.h"

VaihdaTiliaWindow::VaihdaTiliaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaihdaTiliaWindow)
{
    ui->setupUi(this);

    pQTimer = new QTimer(this);
    pQTimer->start(1000);               // tickrate 1sec
    connect(pQTimer, SIGNAL(timeout()), // Timerin signaali
            this,SLOT(updateTimer()));


    // Yhdistetään nappien signaalit
    connect(ui->vaihdaCreditButton,SIGNAL(clicked(bool)),
            this,SLOT(vaihdaCreditButton_handler()));

    connect(ui->vaihdaDebitButton,SIGNAL(clicked(bool)),
            this,SLOT(vaihdaDebitButton_handler()));

}

VaihdaTiliaWindow::~VaihdaTiliaWindow()
{
    delete ui;
    qDebug()<<"VaihdaTiliaWindow tuhottu";
}

// Painetaan Credit -nappia
void VaihdaTiliaWindow::vaihdaCreditButton_handler()
{
    // lähetetään mainwindowille
    emit sendIsCredit(true);
    deleteLater();
}

// Painetaan Dedit -nappia
void VaihdaTiliaWindow::vaihdaDebitButton_handler()
{
    // lähetetään mainwindowille
    emit sendIsCredit(false);
    deleteLater();
}

void VaihdaTiliaWindow::updateTimer()
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
