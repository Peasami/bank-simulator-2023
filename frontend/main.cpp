#include "mainwindow.h"
#include "insertcardwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InsertCardWindow ui;
    ui.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
