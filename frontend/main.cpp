#include "mainwindow.h"
#include "insertcardwindow.h"
#include "lahjoitarahaawindow.h"
#include "naytatapahtumawindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //InsertCardWindow w;
    //NaytaTapahtumaWindow w(nullptr, "120", "hyväntekeväisyys");
    MainWindow w;
    //LahjoitaRahaaWindow w;
    w.show();
    return a.exec();
}
