#ifndef INSERTCARDWINDOW_H
#define INSERTCARDWINDOW_H

#include <QDialog>

namespace Ui {
class InsertCardWindow;
}

class InsertCardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InsertCardWindow(QWidget *parent = nullptr);
    void OpenPINUI();
    ~InsertCardWindow();

private:
    Ui::InsertCardWindow *ui;
};

#endif // INSERTCARDWINDOW_H
