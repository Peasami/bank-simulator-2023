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

    ///TESTI KOODI DEBUGGAUSTA VARTEN ILMAN KORTINLUKIJAA///
    receiveCardNumberFromDLL("06000d8977");

    //Funktiokutsu lukijan avaamiseksi
    pCardReader->openRFIDReader();
    if(pCardReader->openRFIDReader()==true)
    {
        ui->infoLabel->clear();
        qDebug()<<"RFIDlukijaan yhdistäminen onnistui";


    }
    else
    {
        ui->infoLabel->setText("EI YHTEYTTÄ KORTINLUKIJAAN!\nKYTKE KORTINLUKIJA JA\nKÄYNNISTÄ OHJELMA UUDESTAAN!");
        qDebug()<<"RFIDlukijaan yhdistäminen epäonnistui";
    }
    /*delete pMainWindow;
    pMainWindow = nullptr;*/
    QWidget::show();

    ///TESTI KOODI DEBUGGAUSTA VARTEN ILMAN KORTINLUKIJAA///
    //receiveCardNumberFromDLL("06000d8977");
}


void InsertCardWindow::validateLogin()
{
    pRestApi = new DLLRestAPI(this);
    connect(pRestApi, SIGNAL(loginReady()),
            this,SLOT(loginReadySlots()));

    pRestApi->login(cardNumber,pinNumber);

}

void InsertCardWindow::loggedOutSlot(bool state)
{
    if(state==false)
    {
        //Jos login onnistui niin irroitetaan lukijan yhteys
        disconnect(pCardReader,SIGNAL(cardReadSignal(QString)),
                this,SLOT(receiveCardNumberFromDLL(QString)));
        qDebug()<<"lukija disconnect";
    }
    else
    {
        //Mainwindowin lopeta nappi kytkee lukijan yhteyden takaisin
        connect(pCardReader,SIGNAL(cardReadSignal(QString)),
                this,SLOT(receiveCardNumberFromDLL(QString)));

        //Kun mainwindowi tuhotaan niin tuhotaan myös restApiDLL
        pRestApi->deleteLater();
        qDebug()<<"lukija connect";
    }

}

InsertCardWindow::~InsertCardWindow()
{
    delete ui;
    qDebug()<<"insertcardwindow tuhottu";
}

void InsertCardWindow::receiveCardNumberFromDLL(QString cardNum)
{
    qDebug()<<"EXE Vastaanottti DLLSerialPortilta kortinnumeron "<<cardNum;
    cardNumber = cardNum;
    pPinCode = new DLLPinCode(this);
    connect(pPinCode,SIGNAL(pinNumberSignal(QString)),
            this,SLOT(receivePinNumberFromDLL(QString)));
    pPinCode->openPinWindow();
    //loggedOutSlot(false);

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
    token = response.toUtf8();
    qDebug()<<"Saatiin restapi dll:ltä vastaus "+response;
                    qDebug()<<response.length();


    if(QString::compare(response,"Bearer -4078")==0 || response.length()<8)
    {
        ui->infoLabel->setText("EI YHTEYTTÄ TIETOKANTAAN!");
        pPinCode->deleteLater();
        qDebug()<<"ei yhteyttä tietokantaan";
    }
    else
    {
        if(QString::compare(response, "Bearer false")!=0)
        {
            ui->infoLabel->clear();

            loggedOutSlot(false); //katkaisee yhteyden kortinlukijaan

            connect(pRestApi, SIGNAL(httpReady()),
                    this, SLOT(httpReadySlot()));

            pRestApi->getMainwindowInfo(cardNumber);

        }
        else
        {
            ui->infoLabel->clear();
            qDebug()<<"Väärä pin";
            QString info = "VÄÄRÄ PIN!";
            pPinCode->writeInfoText(info);
        }
    }


}

void InsertCardWindow::httpReadySlot()
{
    disconnect(pRestApi, SIGNAL(httpReady()),
            this, SLOT(httpReadySlot()));

    pMainWindow = new MainWindow(this,cardNumber,pRestApi);//,token);

    connect(pMainWindow,SIGNAL(loggedOut(bool)),
            this,SLOT(loggedOutSlot(bool)));

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
        qDebug()<<"Kortilla "+cardNumber<<"debit ja credit molemmat nollia";
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
