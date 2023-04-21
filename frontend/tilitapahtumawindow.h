#ifndef TILITAPAHTUMAWINDOW_H
#define TILITAPAHTUMAWINDOW_H

#include "rivi.h"
#include <QDialog>
#include <qstandarditemmodel.h>


namespace Ui {
class TiliTapahtumaWindow;
}

class TiliTapahtumaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TiliTapahtumaWindow(QWidget *parent = nullptr);
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
};

#endif // TILITAPAHTUMAWINDOW_H
