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

private slots:
        void loginReadySlots();

private:
    Ui::InsertCardWindow *ui;
    DLLSerialPort * pCardReader;
    QString cardNumber;
    QString pinNumber;
    MainWindow * pMainWindow;
    DLLRestAPI * pRestApi;
    DLLPinCode * pPinCode;


#endif // INSERTCARDWINDOW_H

};
