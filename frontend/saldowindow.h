#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H

#include "qjsonarray.h"
#include <QDialog>
#include <qstandarditemmodel.h>

namespace Ui {
class saldoWindow;
}

class saldoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit saldoWindow(QWidget *parent = nullptr, QByteArray tiliData="", bool credit=0);
    ~saldoWindow();


private slots:
    void takaisinButtonHandler();
    void updateTimer();

private:
    Ui::saldoWindow *ui;
    QJsonArray jsonArray;
    QStandardItemModel *taulukkoMalli;
    QTimer * pQTimer;
    short time=10;
    short eventList=0;
    bool identity=0;
};

#endif // SALDOWINDOW_H
