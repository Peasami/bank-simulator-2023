#include "insertcardwindow.h"
#include "ui_insertcardwindow.h"

InsertCardWindow::InsertCardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertCardWindow)
{
    ui->setupUi(this);
    pcardReader = new DLLSerialPort(this);

    connect(pcardReader,SIGNAL(cardReadSignal(QString)),
            this,SLOT(receiveCardNumberFromDLL(QString)));

    //Funktiokutsu lukijan avaamiseksi
    pcardReader->openRFIDReader();
    if(pcardReader->openRFIDReader()==true)
    {
        qDebug()<<"RFIDlukijaan yhdistäminen onnistui";
    }
    else
    {
        qDebug()<<"RFIDlukijaan yhdistäminen epäonnistui";
    }
}

void InsertCardWindow::OpenPINUI()
{

}

InsertCardWindow::~InsertCardWindow()
{
    delete ui;
}

void InsertCardWindow::receiveCardNumberFromDLL(QString cardNum)
{
    qDebug()<<"EXE Vastaanottti DLLSerialPortilta kortinnumeron "<<cardNum;
    cardNumber = cardNum;

}
