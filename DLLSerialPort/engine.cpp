#include "engine.h"

Engine::Engine(QObject *parent):QObject(parent)
{
    qDebug()<<"Engine luotu";
    configureSerialPort();

    //SIGNAL(readyRead() emittoi signaalin joka kerta kun sarjaväylässä on uutta dataa luettavana
    connect(&port,SIGNAL(readyRead()),
            this,SLOT(readData()));
}

Engine::~Engine()
{
    qDebug()<<"Engine tuhottu";
    port.close();
}

bool Engine::openSerialPort()
{
    /* Avataan sarjaväylä vain luku muodossa
     *
     */

    qDebug()<<"openSerialPortissa";
    port.open(QIODevice::ReadOnly);
    if (port.isOpen())
    {
        qDebug()<<port.error();
        return true;
    }
    else
    {
        qDebug()<<port.error();
        return false;
    }
}

void Engine::readData()
{
    /*  Tätä funktiota kutsutaan QSerialPortin readyRead emittoimalla signaalilla
     *  Aina kun lukija saa dataa luettavaksi suoritetaan tämä funktio
     */

    //luetaan kaikki data portista
    const QByteArray data = port.readAll();
    //qDebug()<<data;

    //luetaan merkit väliltä 3-10
    QString dataToString = QString(data).mid(3,10);
    qDebug()<<"Tämä on engine.cpp:ssä kortinnumero"<<dataToString;
    emit sendNumberToInterface(dataToString);
}

void Engine::configureSerialPort()
{
    /* Tällä funktiolla haetaan RFID-lukijan oikea portti saatavilla olevista porteista.
     *
     */

    qDebug()<<"Konfiguroidaan oikea serial portti";

    //haetaan kaikki saatavilla olevat sarjaportit muistiin
    QList<QSerialPortInfo> ports = info.availablePorts();

    /*
    //etsitään onko millään sarjaportilla sarjanumeroa
    foreach (const QSerialPortInfo &info, ports)
    {
        if (info.serialNumber() != "")
        {
            qDebug() << "Portilla" << info.portName() << "on sarjanumero" << info.serialNumber();
        }
        else
        {
            qDebug() << "Portilla" << info.portName() << "ei ole sarjanumeroa";
        }
    }
    */

    //Lukijan sarjanumero löydetty ja asetettu QSrtingiin
    QString serialNumber = "OL56E09005B8EB9";

    //Käy porttilistan läpi ja asettaa portiksi sarjanumeroa vastaavan portin
    foreach (const QSerialPortInfo &info, ports)
    {
        if (info.serialNumber() == serialNumber)
        {
            qDebug()<<"Oikea portti on "<<info.portName();
            QString portName = info.portName();
            port.setPortName(portName);
            break;
        }
    }

}
