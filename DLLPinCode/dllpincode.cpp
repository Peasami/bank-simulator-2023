#include "dllpincode.h"

DLLPinCode::DLLPinCode(QObject *parent):QObject(parent)
{
    pinOlio = new pinwindow;
    connect(pinOlio, SIGNAL(sendNumberToInterface(QString)),
            this,SLOT(receivePin(QString)));
}

DLLPinCode::~DLLPinCode()
{
    delete pinOlio;
    pinOlio = nullptr;
    qDebug()<<"pincode dll tuhottu";
}

void DLLPinCode::openPinWindow()
{
    pinOlio->show();
}

void DLLPinCode::writeInfoText(QString info)
{
    pinOlio->setInfoText(info);
}

// receivePin vastaanottaa datan pinwindowilta ja lähettää sen exeen.
void DLLPinCode::receivePin(QString pin)
{
    qDebug()<<"pinwindow lähetti datan "+pin;
    emit pinNumberSignal(pin);
}
