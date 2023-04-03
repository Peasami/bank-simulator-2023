#include "insertcardwindow.h"
#include "ui_insertcardwindow.h"

InsertCardWindow::InsertCardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertCardWindow)
{
    ui->setupUi(this);
}

void InsertCardWindow::OpenPINUI()
{

}

InsertCardWindow::~InsertCardWindow()
{
    delete ui;
}
