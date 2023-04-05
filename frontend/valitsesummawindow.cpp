#include "valitsesummawindow.h"
#include "ui_valitsesummawindow.h"

ValitseSummaWindow::ValitseSummaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValitseSummaWindow)
{
    ui->setupUi(this);


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
}

void ValitseSummaWindow::summaButtonHandler()
{
    // Hakee signaalin lähettäjän nimen, ja poistaa ensimmäisen kirjaimen
    QObject* buttonSender = sender();
    QString selectedSumma = buttonSender->objectName();
    selectedSumma.remove(0,1);

    if(selectedSumma.at(0).isLetter()){
        qDebug()<<"isLetter";
        done(0);
    }
    else{
        qDebug()<<"isNumber";
        emit sendSumma(selectedSumma);
        done(0);
    }
    qDebug()<<selectedSumma;
}
