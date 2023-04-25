#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(QObject * parent = nullptr);
    ~Engine();
    bool openSerialPort();

private slots:
    void readData();

signals:
    void sendNumberToInterface(QString);

private:
    void configureSerialPort();
    QSerialPort port;
    QSerialPortInfo info;

};

#endif // ENGINE_H
