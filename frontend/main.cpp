#include "insertcardwindow.h"
#include "mainwindow.h" // Debuggausta varten,jos mainwindow pitää saada auki ilman kortinlukijaa
#include "dllpincode.h" // Jos jostain syystä tarvii debugata PIN-ikkunaa erikseen
#include <QApplication>

bool mWindowTest=0;     // mainwindow:n testaus päällä jos 1
bool pinWindowTest=0;   // PINui:n testaus päällä jos 1 ja mWindowTest 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    MainWindow w;
    w.show();
=======
    InsertCardWindow w;

//    if (mWindowTest==0&&pinWindowTest==0)
//    {
//        InsertCardWindow w;

//    }
//    else
//    {
//        if(mWindowTest==1)
//        {
//            MainWindow w;
//            w.show();
//        }
//        else
//        {
//            if(pinWindowTest==1)
//            {
//                DLLPinCode w;
//                w.openPinWindow();
//            }
//        }
//    }
>>>>>>> origin
    return a.exec();
}
