#include "vaihdatiliawindow.h"
#include "ui_vaihdatiliawindow.h"

VaihdaTiliaWindow::VaihdaTiliaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaihdaTiliaWindow)
{
    ui->setupUi(this);

    connect(ui->vaihdaCreditButton,SIGNAL(clicked(bool)),
            this,SLOT(vaihdaCreditButton_handler()));

    connect(ui->vaihdaDebitButton,SIGNAL(clicked(bool)),
            this,SLOT(vaihdaDebitButton_handler()));

}

VaihdaTiliaWindow::~VaihdaTiliaWindow()
{
    delete ui;
}

void VaihdaTiliaWindow::vaihdaCreditButton_handler()
{
    emit sendIsCredit(true);
    done(0);
}

void VaihdaTiliaWindow::vaihdaDebitButton_handler()
{
    emit sendIsCredit(false);
    done(0);
}
