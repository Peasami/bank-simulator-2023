#include "pinwindow.h"
#include "ui_pinwindow.h"



pinwindow::pinwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinwindow)
{
    ui->setupUi(this);

    // create a list of buttons from the children of buttonFrame
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

void pinwindow::on_clearButton_clicked()
{
    ui->lineEdit->clear();
    pin = "";
    qDebug()<<"pin cleared!";
}


void pinwindow::on_okButton_clicked()
{
    qDebug()<<"ok-nappi painettu";
    qDebug()<<pin;
    yritykset--;

    if(pin == oikeaPin)
    {
        qDebug()<<"oikea pin!";
        //emit oikeaPin;
    }
    else
    {
        qDebug()<<"väärä pin!";
    }
    if(yritykset == 0)
    {
        qDebug()<<"kortti lukittu!";
    }

    ui->lineEdit->clear();
    pin = "";
    qDebug()<<"pin cleared!";
}

