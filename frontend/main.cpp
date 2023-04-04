#include "mainwindow.h"
#include "insertcardwindow.h"
#include "lahjoitarahaawindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //InsertCardWindow w;

    MainWindow w;
    //LahjoitaRahaaWindow w;
    w.show();
    return a.exec();
}
