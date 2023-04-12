#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QObject *parent):QObject(parent)
{
    qDebug()<<"DLLSerialPort luotu";
    pEngine = new Engine(this);
    connect(pEngine,SIGNAL(sendNumberToInterface(QString)),
            this,SLOT(receiveNumberFromEngine(QString)));

}

DLLSerialPort::~DLLSerialPort()
{
    qDebug()<<"DLLSerialPort tuhottu";
}

bool DLLSerialPort::openRFIDReader()
{
    /* Funktiokutsulla avataan sarjaportti
     *
     */
    qDebug()<<"openRFIDReaderissa";
    pEngine->openSerialPort();
    if(pEngine->openSerialPort()==true)
    {
        qDebug()<<"Sarjaporttiin yhdistäminen onnistui";
        return true;
    }
    else
    {
        qDebug()<<"Sarjaporttiin yhdistäminen epäonnistui";
        return false;
    }
}

void DLLSerialPort::receiveNumberFromEngine(QString cardNum)
{
    emit cardReadSignal(cardNum);
}
