#include "pinwindow.h"
#include "ui_pinwindow.h"



pinwindow::pinwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinwindow)
{
    ui->setupUi(this);

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

}

pinwindow::~pinwindow()
{
    delete ui;
}

// Asettaa painettujen numeronappien tekstin lineEdittiin ja teksti tallentuu "pin"-muuttujaan.
// Echomode estää lineEdittiin saapuvan tekstin näkymisen UI:ssa.
void pinwindow::numButtonClickHandler()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    ;
    if(button)
    {
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
    else
    {
        qDebug()<<"kortti lukittu";
    }
    yritykset--;
    ui->lineEdit->clear();
    pin = "";

}

