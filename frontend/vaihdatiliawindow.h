#ifndef VAIHDATILIAWINDOW_H
#define VAIHDATILIAWINDOW_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class VaihdaTiliaWindow;
}

class VaihdaTiliaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VaihdaTiliaWindow(QWidget *parent = nullptr);
    ~VaihdaTiliaWindow();

signals:
    void sendIsCredit(bool);
    void deleteWindow(QWidget* = nullptr); // Voidaan kutsua antamalla pointteri, tuhoaa pointterin osoittaman olion.

private slots:
    void vaihdaCreditButton_handler();
    void vaihdaDebitButton_handler();

private:
    Ui::VaihdaTiliaWindow *ui;
};

#endif // VAIHDATILIAWINDOW_H
