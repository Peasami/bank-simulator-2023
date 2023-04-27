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
    createRestApi();
    ///TESTI KOODI DEBUGGAUSTA VARTEN ILMAN KORTINLUKIJAA///
    //receiveCardNumberFromDLL("06000d8977");
}


void InsertCardWindow::validateLogin()
{

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
        //pRestApi->deleteLater();
        delete pRestApi;
        pRestApi=nullptr;
        createRestApi();


        qDebug()<<"lukija connect ja restapi luotu uudelleen";
    }

}

InsertCardWindow::~InsertCardWindow()
{
    delete ui;
    qDebug()<<"insertcardwindow tuhottu";
}

void InsertCardWindow::receiveCardNumberFromDLL(QString cardNum)
{
    ui->infoLabel->clear();
    qDebug()<<"EXE Vastaanottti DLLSerialPortilta kortinnumeron "<<cardNum;
    cardNumber = cardNum;

    connect(pRestApi,SIGNAL(blacklistSignal()),
            this,SLOT(checkIfBlacklisted()));
    pRestApi->checkBlacklist(cardNumber);


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
    disconnect(pRestApi, SIGNAL(loginReady()),
            this,SLOT(loginReadySlots()));

    QString response=pRestApi->getLoginResponse();
    token = response.toUtf8();
    qDebug()<<"Saatiin restapi dll:ltä vastaus "+response;                    


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
            attempts--;
            ui->infoLabel->clear();
            qDebug()<<"Väärä pin";
            QString info = "VÄÄRÄ PIN!";
            pPinCode->writeInfoText(info);
        }
    }
    if(attempts == 0)
    {
        //connect(pRestApi,SIGNAL(updateBlacklistSignal()),
                    //this,SLOT(blacklistUpdated()));
        pRestApi->addToBlacklist(cardNumber);
        attempts = 3;
        ui->infoLabel->setText("Lukitsimme kortin, ota yhteys pankkiin!");
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

void InsertCardWindow::checkIfBlacklisted()
{
    disconnect(pRestApi,SIGNAL(blacklistSignal()),
            this,SLOT(checkIfBlacklisted()));
    QByteArray blacklistData = pRestApi->getHttpResponse();
    qDebug()<<"blacklist data "<<blacklistData;
    /*
    QJsonDocument json_doc = QJsonDocument::fromJson(blacklistData);
    QJsonArray json_array = json_doc.array();
    int state = 0;

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        state += (json_obj["idKortti"].toInt());
    }
    */
    if(blacklistData != "")
    {

        int state = blacklistData.toInt();
        qDebug()<<"exessä state "<<state;
        if(state == 0)
        {
            qDebug()<<"PIN OLIO LUODAAN";
            pPinCode = new DLLPinCode(this);
            connect(pPinCode,SIGNAL(pinNumberSignal(QString)),
                    this,SLOT(receivePinNumberFromDLL(QString)));
            pPinCode->openPinWindow();
        }
        else
        {
            qDebug()<<"kortti lukittu";
            ui->infoLabel->setText("KORTTI LUKITTU!");
        }
    }
    else
    {
        ui->infoLabel->setText("EI YHTEYTTÄ TIETOKANTAAN!");
    }

}
/*
void InsertCardWindow::blacklistUpdated()
{
    qDebug()<<"DLLrestapiin viety kortti";
}
*/
void InsertCardWindow::createRestApi()
{
    pRestApi = new DLLRestAPI(this);
}
