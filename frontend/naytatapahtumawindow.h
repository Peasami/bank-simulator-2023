#ifndef NAYTATAPAHTUMAWINDOW_H
#define NAYTATAPAHTUMAWINDOW_H

#include <QDialog>
#include <QDebug>

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
    void deleteWindow(QWidget* = nullptr); // Voidaan kutsua antamalla pointteri, tuhoaa pointterin osoittaman olion.

private:
    Ui::NaytaTapahtumaWindow *ui;
    QString lahjoitusKohde;
    QString lahjoitusMaara;
};

#endif // NAYTATAPAHTUMAWINDOW_H
