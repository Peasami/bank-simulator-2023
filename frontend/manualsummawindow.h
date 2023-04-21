#ifndef MANUALSUMMAWINDOW_H
#define MANUALSUMMAWINDOW_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ManualSummaWindow;
}

class ManualSummaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManualSummaWindow(QWidget *parent = nullptr);
    ~ManualSummaWindow();

signals:
    void sendSumma(QString);

public slots:
    void okClickHandler();
    void numClickHandler();
    void updateTimer();

private:
    Ui::ManualSummaWindow *ui;
    QTimer *pQTimer;
    short time;
};

#endif // MANUALSUMMAWINDOW_H
