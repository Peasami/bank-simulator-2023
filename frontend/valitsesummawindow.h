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

private slots:
    void summaButtonHandler();

private:
    Ui::ValitseSummaWindow *ui;
};

#endif // VALITSESUMMAWINDOW_H
