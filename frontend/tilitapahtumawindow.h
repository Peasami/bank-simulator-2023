/****************************************
 * Tilitapahtumaikkunan header,         *
 * tarkempi informaatio cpp-tiedostossa *
 ****************************************/
#ifndef TILITAPAHTUMAWINDOW_H
#define TILITAPAHTUMAWINDOW_H

#include "qjsonarray.h"
// #include "rivi.h"
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
    // konstruktorissa lisäparametrit kortin tyypille ja tilin datalle
    explicit TiliTapahtumaWindow(QWidget *parent = nullptr, QByteArray tiliData="", bool credit=0);
    ~TiliTapahtumaWindow();

private slots:
    void takaisinButtonHandler();
    void aiemmatButtonHandler();
    void uudemmatButtonHandler();
    void updateTimer();

private:
    /********************************
     * pois kommentoidut muuttujat  *
     * ja funktiot ovat turhia      *
     ********************************/

    Ui::TiliTapahtumaWindow *ui;
    QStandardItemModel *taulukkoMalli;
    QJsonArray jsonArray;
    void updateTable();
    //rivi * pRivi;
    //bool listaTesti=1;
    QTimer *pQTimer;
    short time=10;
    short sivu=0;
    short sivuMaara=0;
    //short eventList=0;
    short index=0;          // pysyvä indeksimuuttuja
    bool identity=0;        // 0=debit, 1=credit
    //QJsonArray * json_array;
};

#endif // TILITAPAHTUMAWINDOW_H
