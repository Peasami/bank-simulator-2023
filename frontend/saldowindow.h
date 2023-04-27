#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H

#include <QDialog>
#include <qstandarditemmodel.h>

namespace Ui {
class saldoWindow;
}

class saldoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit saldoWindow(QWidget *parent = nullptr, bool a=0);
    ~saldoWindow();


private slots:
    void takaisinButtonHandler();
    void updateTimer();

private:
    Ui::saldoWindow *ui;
    bool listaTesti=1;
    short time=10;
    QTimer *pQTimer;


};

#endif // SALDOWINDOW_H
