#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialPort_global.h"
#include <QObject>
#include <QDebug>
#include "engine.h"


class DLLSERIALPORT_EXPORT DLLSerialPort : public QObject
{
    Q_OBJECT
public:
    DLLSerialPort(QObject * parent = nullptr);
    ~DLLSerialPort();
    bool openRFIDReader();

private slots:
    void receiveNumberFromEngine(QString);

signals:
    void cardReadSignal(QString);

private:
    Engine * pEngine;
};

#endif // DLLSERIALPORT_H
