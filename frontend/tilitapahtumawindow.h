#ifndef TILITAPAHTUMAWINDOW_H
#define TILITAPAHTUMAWINDOW_H

#include "qjsonarray.h"
#include "rivi.h"
#include <QDialog>
#include <qstandarditemmodel.h>
#include <QByteArray>


namespace Ui {
class TiliTapahtumaWindow;
}

class TiliTapahtumaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TiliTapahtumaWindow(QWidget *parent = nullptr, QByteArray tiliData="", bool credit=0);
    ~TiliTapahtumaWindow();

private slots:
    void takaisinButtonHandler();
    void aiemmatButtonHandler();
    void uudemmatButtonHandler();
    void updateTimer();

private:
    Ui::TiliTapahtumaWindow *ui;
    QStandardItemModel *taulukkoMalli;
    QJsonArray jsonArray;
    rivi * pRivi;
    bool listaTesti=1;
    QTimer *pQTimer;
    short time=10;
    short sivu=0;
    short edellinenSivu=0;
    short eventList=0;
    short index=0;
    bool identity=0;
    //QJsonArray * json_array;
};

#endif // TILITAPAHTUMAWINDOW_H
