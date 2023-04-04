#ifndef LAHJOITARAHAAWINDOW_H
#define LAHJOITARAHAAWINDOW_H

#include <QDialog>

namespace Ui {
class LahjoitaRahaaWindow;
}

class LahjoitaRahaaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LahjoitaRahaaWindow(QWidget *parent = nullptr);
    ~LahjoitaRahaaWindow();

signals:
    void sendCharity(QString);

private slots:
    void charityButtonHandler();

private:
    Ui::LahjoitaRahaaWindow *ui;
    QStringList charityList;
};

#endif // LAHJOITARAHAAWINDOW_H
