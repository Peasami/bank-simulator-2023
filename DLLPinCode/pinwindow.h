#ifndef PINWINDOW_H
#define PINWINDOW_H

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

private:
    Ui::pinwindow *ui;
};

#endif // PINWINDOW_H
