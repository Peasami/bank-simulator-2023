#ifndef NAYTATAPAHTUMAWINDOW_H
#define NAYTATAPAHTUMAWINDOW_H

#include <QDialog>

namespace Ui {
class NaytaTapahtumaWindow;
}

class NaytaTapahtumaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NaytaTapahtumaWindow(QWidget *parent = nullptr);
    ~NaytaTapahtumaWindow();

    void setLahjoitusMaara(const QString &newLahjoitusMaara);
    void setLahjoitusKohde(const QString &newLahjoitusKohde);
    void updateInfo();

private:
    Ui::NaytaTapahtumaWindow *ui;
    QString lahjoitusKohde;
    QString lahjoitusMaara;
};

#endif // NAYTATAPAHTUMAWINDOW_H
