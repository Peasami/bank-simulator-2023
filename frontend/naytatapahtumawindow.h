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

    void setTapahtumaMaara(const QString &newTapahtumaMaara);
    void setTapahtumaNimi(const QString &newTapahtumaNimi);
    void setTapahtumaInfo(const QString &newTapahtumaInfo);
    void updateInfo();

public slots:
    void updateTimer();

signals:
    void endSession();

private:
    Ui::NaytaTapahtumaWindow *ui;
    QString tapahtumaNimi;
    QString tapahtumaMaara;
    QString tapahtumaInfo;
    QTimer *pQTimer;
    short time=5;
};

#endif // NAYTATAPAHTUMAWINDOW_H
