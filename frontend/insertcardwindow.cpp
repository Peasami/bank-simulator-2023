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

    }
    else
    {
        qDebug()<<"RFIDlukijaan yhdistäminen epäonnistui";
    }
    /*delete pMainWindow;
    pMainWindow = nullptr;*/
    QWidget::show();
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

    pPinCode = new DLLPinCode(this);
    connect(pPinCode,SIGNAL(pinNumberSignal(QString)),
            this,SLOT(receivePinNumberFromDLL(QString)));



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

            connect(pRestApi, SIGNAL(httpReady()),
                    this, SLOT(httpReadySlot()));

            pRestApi->getMainwindowInfo(cardNumber);

        }
        else
        {
            qDebug()<<"Väärä pin";
           // pPinCode->
        }
    }


}

void InsertCardWindow::httpReadySlot()
{
    delete pPinCode;
    pPinCode=nullptr;

    QByteArray username = pRestApi->getHttpResponse();
    QJsonDocument json_doc = QJsonDocument::fromJson(username);
    QJsonArray json_array = json_doc.array();
    QString name;
    QString cardType;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        name += json_obj["Etunimi"].toString()+" "+json_obj["Sukunimi"].toString();
        cardType += QString::number(json_obj["Debit"].toInt())+QString::number(json_obj["Credit"].toInt());
    }
    qDebug()<<"Kortin tyyppi "+cardType;

    switch(cardType.toInt()){
    case 0:
        delete pMainWindow;
        pMainWindow=nullptr;
        return;
    case 1:
        pMainWindow->IsCredit(true);
        pMainWindow->disableVaihdaBtn();
        break;
    case 10:
        pMainWindow->IsCredit(false);
        pMainWindow->disableVaihdaBtn();
        break;
    case 11:
        pMainWindow->IsCredit(false);
        break;
    }

    pMainWindow->SetUserName(name);

    pMainWindow->show();

    qDebug()<<"Insertcardwindowiin response: "<<username;
}
