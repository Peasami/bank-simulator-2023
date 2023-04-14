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
    void deleteWindow(QWidget* = nullptr); // Voidaan kutsua antamalla pointteri, tuhoaa pointterin osoittaman olion.

public slots:
    void okClickHandler();
    void numClickHandler();

private:
    Ui::ManualSummaWindow *ui;
};

#endif // MANUALSUMMAWINDOW_H
