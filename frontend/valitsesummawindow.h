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
    void endSession();
private slots:
    void summaButtonHandler();
    void updateTimer();

private:
    Ui::ValitseSummaWindow *ui;
    QTimer *pQTimer;
    int testiSaldo = 150;
    short time=10;
};

#endif // VALITSESUMMAWINDOW_H
