#ifndef INSERTCARDWINDOW_H
#define INSERTCARDWINDOW_H

#include <QDialog>
#include "dllserialport.h"
#include "mainwindow.h"

namespace Ui {
class InsertCardWindow;
}

class InsertCardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertCardWindow(QWidget *parent = nullptr);
    void OpenPINUI();
    ~InsertCardWindow();

public slots:
        void receiveCardNumberFromDLL(QString);

private:
    Ui::InsertCardWindow *ui;
    DLLSerialPort * pcardReader;
    QString cardNumber;
    QString pinNumber;
    MainWindow * pMainWindow;

#endif // INSERTCARDWINDOW_H

};
