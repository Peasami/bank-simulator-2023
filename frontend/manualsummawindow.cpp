#include "manualsummawindow.h"
#include "ui_manualsummawindow.h"
#include <QTimer>

ManualSummaWindow::ManualSummaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualSummaWindow)
{
    ui->setupUi(this);

    // OKButtonille ja Clearbuttonille omat handlerit
    connect(ui->OKButton, SIGNAL(clicked(bool)),
            this,SLOT(okClickHandler()));


    // Käy läpi kaikki buttonLayout widgetit
    for(int i=0;i<ui->buttonLayout->count();i++)
    {
        // jos nappi alkaa kirjaimella "b", yhdistää sen numClickHandleriin
        if(ui->buttonLayout->itemAt(i)->widget()->objectName().startsWith("b") == true)
        {
            qDebug()<<"connecting to: "<<ui->buttonLayout->itemAt(i)->widget()->objectName();
            connect(ui->buttonLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                    this,SLOT(numClickHandler()));
        }

    }
}

ManualSummaWindow::~ManualSummaWindow()
{
    delete ui;
    qDebug()<<"ManualSummaWindow tuhottu";
}

void ManualSummaWindow::okClickHandler()
{
    qDebug()<<"ManualSummaWindow";
    QString manualSummaEdit = ui->summaEdit->text();
    emit sendSumma(manualSummaEdit);
    qDebug()<<manualSummaEdit;
    deleteLater();
}

void ManualSummaWindow::numClickHandler()
{
    time=10;
    // Hakee signaalin lähettäjän nimen, ja poistaa ensimmäisen kirjaimen
    QObject * buttonSender = sender();
    QString selectedSumma = buttonSender->objectName();
    selectedSumma.remove(0,1); // Poistetaan ensimmäinen kirjain

    ui->summaEdit->insert(selectedSumma);
}

void ManualSummaWindow::updateTimer()
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
