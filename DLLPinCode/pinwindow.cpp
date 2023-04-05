#include "pinwindow.h"
#include "ui_pinwindow.h"

pinwindow::pinwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinwindow)
{
    ui->setupUi(this);
}

pinwindow::~pinwindow()
{
    delete ui;
}
