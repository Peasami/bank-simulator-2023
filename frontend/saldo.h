#ifndef SALDO_H
#define SALDO_H

#include <QDialog>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Saldo;
}

class Saldo : public QDialog
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent = nullptr);
    ~Saldo();

private:
    Ui::Saldo *ui;
};

#endif // SALDO_H
