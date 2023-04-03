#include "vaihdatiliawindow.h"
#include "ui_vaihdatiliawindow.h"

VaihdaTiliaWindow::VaihdaTiliaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VaihdaTiliaWindow)
{
    ui->setupUi(this);
}

VaihdaTiliaWindow::~VaihdaTiliaWindow()
{
    delete ui;
}
