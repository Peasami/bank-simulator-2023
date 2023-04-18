#ifndef VALITSESUMMAWINDOW_H
#define VALITSESUMMAWINDOW_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ValitseSummaWindow;
}

class ValitseSummaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ValitseSummaWindow(QWidget *parent = nullptr);
    ~ValitseSummaWindow();

signals:
    void sendSumma(QString);
    void requestManualSumma();
    void deleteWindow(QWidget* = nullptr); // Voidaan kutsua antamalla pointteri, tuhoaa pointterin osoittaman olion.

private slots:
    void summaButtonHandler();

private:
    Ui::ValitseSummaWindow *ui;

    int testiSaldo = 150;
};

#endif // VALITSESUMMAWINDOW_H
