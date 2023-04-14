#include "insertcardwindow.h"
#include "mainwindow.h" // Debuggausta varten,jos mainwindow pitää saada auki ilman kortinlukijaa

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InsertCardWindow w;
    w.show();
    return a.exec();
}
