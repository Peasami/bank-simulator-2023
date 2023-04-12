#include "insertcardwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InsertCardWindow w;
    w.show();
    return a.exec();
}
