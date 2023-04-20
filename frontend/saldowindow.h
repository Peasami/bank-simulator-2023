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
    explicit saldoWindow(QWidget *parent = nullptr);
    ~saldoWindow();


private slots:
    void takaisinButtonHandler();

private:
    Ui::saldoWindow *ui;
    bool listaTesti=1;
};

#endif // SALDOWINDOW_H