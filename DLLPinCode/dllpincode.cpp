#include "dllpincode.h"

DLLPinCode::DLLPinCode(QObject *parent):QObject(parent)
{
    pinOlio = new pinwindow;
    connect(pinOlio, SIGNAL(sendNumberToInterface(QString)),
            this,SLOT(receivePin(QString)));
}

void DLLPinCode::openPinWindow()
{

    pinOlio->show();

}

void DLLPinCode::receivePin(QString pin)
{
    qDebug()<<"pinwidow lähetti datan "+pin;
    emit pinNumberSignal(pin);
}
