#include "insertcardwindow.h"
#include "ui_insertcardwindow.h"

InsertCardWindow::InsertCardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertCardWindow)
{
    ui->setupUi(this);
    pCardReader = new DLLSerialPort(this);

    connect(pCardReader,SIGNAL(cardReadSignal(QString)),
            this,SLOT(receiveCardNumberFromDLL(QString)));

    //Funktiokutsu lukijan avaamiseksi
    pCardReader->openRFIDReader();
    if(pCardReader->openRFIDReader()==true)
    {
        qDebug()<<"RFIDlukijaan yhdistäminen onnistui";
        pPinCode = new DLLPinCode(this);
        connect(pPinCode,SIGNAL(pinNumberSignal(QString)),
                this,SLOT(receivePinNumberFromDLL(QString)));

    }
    else
    {
        qDebug()<<"RFIDlukijaan yhdistäminen epäonnistui";
    }




}

void InsertCardWindow::validateLogin()
{
    pRestApi = new DLLRestAPI(this);
    connect(pRestApi, SIGNAL(loginReady()),
            this,SLOT(loginReadySlots()));

    pRestApi->login(cardNumber,pinNumber);

}

InsertCardWindow::~InsertCardWindow()
{
    delete ui;
}

void InsertCardWindow::receiveCardNumberFromDLL(QString cardNum)
{
    qDebug()<<"EXE Vastaanottti DLLSerialPortilta kortinnumeron "<<cardNum;
    cardNumber = cardNum;
    pPinCode->openPinWindow();

}

void InsertCardWindow::receivePinNumberFromDLL(QString pin)
{
    qDebug()<<"EXE Vastaanottti DLLPinCodelta pinnin "<<pin;
    pinNumber = pin;
    validateLogin();
}

void InsertCardWindow::loginReadySlots()
{
    QString response=pRestApi->getLoginResponse();
    qDebug()<<"Saatiin restapi dll:ltä vastaus "+response;
                    qDebug()<<response.length();


    if(QString::compare(response,"Bearer -4078")==0 || response.length()<8)
    {
        qDebug()<<"ei yhteyttä tietokantaan";
    }
    else
    {
        if(QString::compare(response, "Bearer false")!=0)
        {
            //Tähän kohtaan getillä asiakkaan tiedot
            pMainWindow = new MainWindow(this);
            pMainWindow->show();
        }
        else
        {
            qDebug()<<"Väärä pin";
        }
    }
}
