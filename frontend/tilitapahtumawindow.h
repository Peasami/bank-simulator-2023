#ifndef TILITAPAHTUMAWINDOW_H
#define TILITAPAHTUMAWINDOW_H

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
    rivi * pRivi;
    bool listaTesti=1;
    QTimer *pQTimer;
    short time;
    short page=0;
    //QJsonArray * json_array;
};

#endif // TILITAPAHTUMAWINDOW_H
