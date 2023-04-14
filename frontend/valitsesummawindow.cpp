#include "valitsesummawindow.h"
#include "ui_valitsesummawindow.h"

ValitseSummaWindow::ValitseSummaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValitseSummaWindow)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose); // Olio tuhoutuu ruksia painaessa


    // Käy läpi kaikki napit
    for(int i=0;i<3;i++)
    {
        // Yhdistää kaikki nappien clicked signaalit yhteen buttonhandleriin
        connect(ui->leftSummaLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(summaButtonHandler()));
        connect(ui->rightSummaLayout->itemAt(i)->widget(),SIGNAL(clicked()),
                this,SLOT(summaButtonHandler()));
    }
}

ValitseSummaWindow::~ValitseSummaWindow()
{
    delete ui;
    qDebug()<<"valitseSummaWindow Tuhottu";
}

void ValitseSummaWindow::summaButtonHandler()
{
    // Hakee signaalin lähettäjän nimen, ja poistaa ensimmäisen kirjaimen
    QObject* buttonSender = sender();
    QString selectedSumma = buttonSender->objectName();
    selectedSumma.remove(0,1); // Poistetaan ensimmäinen kirjain


    if(selectedSumma.at(0).isLetter()) // Jos nappi on "valise muu summa" -nappi
    {
        qDebug()<<"isLetter";
        emit requestManualSumma();
        emit deleteWindow(this);
    }
    else
    {
        qDebug()<<"isNumber";
        if(selectedSumma.toInt() > testiSaldo){
            qDebug()<<"Ei tarpeeksi saldoa!";
            done(0);
            emit deleteWindow(this);
        }
        testiSaldo -= selectedSumma.toInt();
        qDebug()<<"Nostit "<<selectedSumma<<"€. Saldosi: "<<testiSaldo;
        emit sendSumma(selectedSumma);
        emit deleteWindow(this);
    }
    qDebug()<<selectedSumma;
}