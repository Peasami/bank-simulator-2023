#include "insertcardwindow.h"
#include "mainwindow.h" // Debuggausta varten,jos mainwindow pitää saada auki ilman kortinlukijaa
#include "dllpincode.h" // Jos jostain syystä tarvii debugata PIN-ikkunaa erikseen
#include <QApplication>

bool mWindowTest=0;     // mainwindow:n testaus päällä jos 1
bool pinWindowTest=0;   // PINui:n testaus päällä jos 1 ja mWindowTest 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (mWindowTest==pinWindowTest==0)
    {
        InsertCardWindow w;
        w.show();
    }
    else
    {
        if(mWindowTest==1)
        {
            MainWindow w;
            w.show();
        }
        else
        {
            if(pinWindowTest==1)
            {
                DLLPinCode w;
                w.openPinWindow();
            }
        }
    }

    return a.exec();
}
