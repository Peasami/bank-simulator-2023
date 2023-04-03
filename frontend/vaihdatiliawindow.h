#ifndef VAIHDATILIAWINDOW_H
#define VAIHDATILIAWINDOW_H

#include <QDialog>

namespace Ui {
class VaihdaTiliaWindow;
}

class VaihdaTiliaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VaihdaTiliaWindow(QWidget *parent = nullptr);
    ~VaihdaTiliaWindow();

private:
    Ui::VaihdaTiliaWindow *ui;
};

#endif // VAIHDATILIAWINDOW_H
