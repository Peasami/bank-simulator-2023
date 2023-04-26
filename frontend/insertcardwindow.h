#ifndef INSERTCARDWINDOW_H
#define INSERTCARDWINDOW_H

#include <QDialog>
#include "dllserialport.h"
#include "dllrestapi.h"
#include "dllpincode.h"
#include "mainwindow.h"

namespace Ui {
class InsertCardWindow;
}

class InsertCardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertCardWindow(QWidget *parent = nullptr);
    ~InsertCardWindow();
    void validateLogin();


public slots:
        void receiveCardNumberFromDLL(QString);
        void receivePinNumberFromDLL(QString);
        void loggedOutSlot(bool);

private slots:
        void loginReadySlots();
        void httpReadySlot();
        void checkIfBlacklisted();

private:
    Ui::InsertCardWindow *ui;
    DLLSerialPort * pCardReader;
    QString cardNumber;
    QString pinNumber;
    QByteArray token;
    MainWindow * pMainWindow;
    DLLRestAPI * pRestApi;
    DLLPinCode * pPinCode;


#endif // INSERTCARDWINDOW_H

};
