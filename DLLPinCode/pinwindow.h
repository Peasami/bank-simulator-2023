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
    void setInfoText(QString);

private slots:
    void numButtonClickHandler();
    void on_clearButton_clicked();
    void on_okButton_clicked();
    void updateTimer();

signals:
    void sendNumberToInterface(QString);

protected:

private:
    Ui::pinwindow *ui;    
    QString pin;    
    int yritykset = 3;
    QTimer *pQTimer;
    short time = 10;
    QString normalText = "Näppäile tunnusluku ja paina OK";
};

#endif // PINWINDOW_H
