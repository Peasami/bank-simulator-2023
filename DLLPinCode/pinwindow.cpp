#include "pinwindow.h"
#include "ui_pinwindow.h"
#include <QTimer>

pinwindow::pinwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinwindow)
{
    ui->setupUi(this);

    pQTimer = new QTimer(this);
    pQTimer->start(1000); // tickrate 1sec

    connect(pQTimer, SIGNAL(timeout()),
    this,SLOT(updateTimer()));

    // Luodaan GUI:ssa frame ja asetetaan sen sisään napit muodostaen niille yhteyden.
    // Kaikki napit joissa tekstinkoko == 1, connectataan clickhandleriin.
    QListIterator buttonList (ui->frame->children());
    while (buttonList.hasNext())
    {
        QPushButton *button = qobject_cast<QPushButton*>(buttonList.next());
        if (button)
        {
            if (button->text().size()== 1)
            {
                connect(button, SIGNAL(clicked()),
                this, SLOT(numButtonClickHandler())
                );
            }
        }
    }
    qDebug()<<"pin-ikkuna aukeaa";
}

pinwindow::~pinwindow()
{
    delete ui;
    qDebug()<<"pinwindow tuhottu";
}

// Asettaa painettujen numeronappien tekstin lineEdittiin ja teksti tallentuu "pin"-muuttujaan.
// Echomode estää lineEdittiin saapuvan tekstin näkymisen UI:ssa.
void pinwindow::numButtonClickHandler()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    if(button)
    {
        time=10;
        pQTimer->start(1000); // tickrate 1sec
        ui->lineEdit->setEchoMode(QLineEdit::Password);

        pin.append(button->text());
        ui->lineEdit->setText(pin);
        qDebug()<<pin;
    }
}

// Clear-napilla tyhjennetään lineEdit sekä asetetaan "pin"-muuttuja takaisin nollaan.
void pinwindow::on_clearButton_clicked()
{
    ui->lineEdit->clear();
    pin = "";
    qDebug()<<"pin cleared!";
}

// Ok-nappi lähettää lineEditissä olevan pin-muuttujan interfaceen
// Jos yritykset menee nollaan, kortti lukitaan.
void pinwindow::on_okButton_clicked()
{
    qDebug()<<"ok-nappi painettu";
    qDebug()<<"käyttäjä syötti "+pin;

    if(yritykset > 0)
    {
        emit sendNumberToInterface(pin);
    }

    //yritykset--;
    ui->lineEdit->clear();
    pin = "";
    time=10;
}
// Aikakatkaisu-toiminto, jolla suljetaan PIN UI
// jos käyttäjä ei tee mitään 10 sekunttiin.
void pinwindow::updateTimer()
{
    time--;
    qDebug()<<time;
    qDebug()<<"yrityksiä jäljellä"<<+yritykset;

    if(time == 0 || yritykset == 0)
    {
        qDebug()<<"timeout";
        done(0);
        pQTimer->stop();
        deleteLater();
    }
    if(time%3==0)
    {
        ui->label->setText(normalText);
    }
}

void pinwindow::setInfoText(QString info)
{
    ui->label->setText(info);
    yritykset--;
}
