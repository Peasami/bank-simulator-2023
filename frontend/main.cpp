#include "insertcardwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //InsertCardWindow w;
    MainWindow w;
    w.show();
    return a.exec();
}
