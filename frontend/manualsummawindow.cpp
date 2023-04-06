#include "manualsummawindow.h"
#include "ui_manualsummawindow.h"

ManualSummaWindow::ManualSummaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualSummaWindow)
{
    ui->setupUi(this);

    connect(ui->OKButton, SIGNAL(clicked(bool)),
            this,SLOT(clickHandler()));
}

ManualSummaWindow::~ManualSummaWindow()
{
    delete ui;
}

void ManualSummaWindow::clickHandler()
{
    qDebug()<<"ManualSummaWindow";
    QString manualSummaEdit = ui->summaEdit->text();
    emit sendSumma(manualSummaEdit);
    qDebug()<<manualSummaEdit;
    done(0);
}
