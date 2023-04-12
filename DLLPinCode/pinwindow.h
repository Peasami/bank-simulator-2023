#ifndef PINWINDOW_H
#define PINWINDOW_H
#include <QDebug>
#include <QDialog>

namespace Ui {
class pinwindow;
}

class pinwindow : public QDialog
{
    Q_OBJECT

public:
    explicit pinwindow(QWidget *parent = nullptr);
    ~pinwindow();


private slots:
    void numButtonClickHandler();
    void on_clearButton_clicked();
    void on_okButton_clicked();

signals:
    void sendNumberToInterface(QString);

protected:


private:
    Ui::pinwindow *ui;
    bool pinGiven = false;
    QString pin;
    //QString oikeaPin = "1234";
    int yritykset = 3;
};

#endif // PINWINDOW_H
