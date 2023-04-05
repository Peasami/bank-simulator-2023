/********************************************************************************
** Form generated from reading UI file 'pinwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINWINDOW_H
#define UI_PINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_pinwindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *num1Button;
    QPushButton *num9Button;
    QPushButton *num7Button;
    QPushButton *num5Button;
    QPushButton *num6Button;
    QPushButton *num8Button;
    QPushButton *num3Button;
    QPushButton *num2Button;
    QPushButton *num4Button;
    QPushButton *num0Button;
    QPushButton *okButton;
    QPushButton *clearButton;

    void setupUi(QDialog *pinwindow)
    {
        if (pinwindow->objectName().isEmpty())
            pinwindow->setObjectName(QString::fromUtf8("pinwindow"));
        pinwindow->resize(323, 347);
        verticalLayout_2 = new QVBoxLayout(pinwindow);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(pinwindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(pinwindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe UI"));
        font1.setPointSize(24);
        lineEdit->setFont(font1);

        verticalLayout_2->addWidget(lineEdit);

        frame = new QFrame(pinwindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        num1Button = new QPushButton(frame);
        num1Button->setObjectName(QString::fromUtf8("num1Button"));
        num1Button->setMinimumSize(QSize(0, 50));
        QFont font2;
        font2.setPointSize(12);
        num1Button->setFont(font2);

        gridLayout->addWidget(num1Button, 0, 0, 1, 1);

        num9Button = new QPushButton(frame);
        num9Button->setObjectName(QString::fromUtf8("num9Button"));
        num9Button->setMinimumSize(QSize(0, 50));
        num9Button->setFont(font2);

        gridLayout->addWidget(num9Button, 2, 2, 1, 1);

        num7Button = new QPushButton(frame);
        num7Button->setObjectName(QString::fromUtf8("num7Button"));
        num7Button->setMinimumSize(QSize(0, 50));
        num7Button->setFont(font2);

        gridLayout->addWidget(num7Button, 2, 0, 1, 1);

        num5Button = new QPushButton(frame);
        num5Button->setObjectName(QString::fromUtf8("num5Button"));
        num5Button->setMinimumSize(QSize(0, 50));
        num5Button->setFont(font2);

        gridLayout->addWidget(num5Button, 1, 1, 1, 1);

        num6Button = new QPushButton(frame);
        num6Button->setObjectName(QString::fromUtf8("num6Button"));
        num6Button->setMinimumSize(QSize(0, 50));
        num6Button->setFont(font2);

        gridLayout->addWidget(num6Button, 1, 2, 1, 1);

        num8Button = new QPushButton(frame);
        num8Button->setObjectName(QString::fromUtf8("num8Button"));
        num8Button->setMinimumSize(QSize(0, 50));
        num8Button->setFont(font2);

        gridLayout->addWidget(num8Button, 2, 1, 1, 1);

        num3Button = new QPushButton(frame);
        num3Button->setObjectName(QString::fromUtf8("num3Button"));
        num3Button->setMinimumSize(QSize(0, 50));
        num3Button->setFont(font2);

        gridLayout->addWidget(num3Button, 0, 2, 1, 1);

        num2Button = new QPushButton(frame);
        num2Button->setObjectName(QString::fromUtf8("num2Button"));
        num2Button->setMinimumSize(QSize(0, 50));
        num2Button->setFont(font2);

        gridLayout->addWidget(num2Button, 0, 1, 1, 1);

        num4Button = new QPushButton(frame);
        num4Button->setObjectName(QString::fromUtf8("num4Button"));
        num4Button->setMinimumSize(QSize(0, 50));
        num4Button->setFont(font2);

        gridLayout->addWidget(num4Button, 1, 0, 1, 1);

        num0Button = new QPushButton(frame);
        num0Button->setObjectName(QString::fromUtf8("num0Button"));
        num0Button->setMinimumSize(QSize(0, 50));
        num0Button->setFont(font2);

        gridLayout->addWidget(num0Button, 3, 1, 1, 1);

        okButton = new QPushButton(frame);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setMinimumSize(QSize(0, 50));
        okButton->setFont(font2);

        gridLayout->addWidget(okButton, 3, 2, 1, 1);

        clearButton = new QPushButton(frame);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(clearButton, 3, 0, 1, 1);


        verticalLayout_2->addWidget(frame);


        retranslateUi(pinwindow);

        QMetaObject::connectSlotsByName(pinwindow);
    } // setupUi

    void retranslateUi(QDialog *pinwindow)
    {
        pinwindow->setWindowTitle(QCoreApplication::translate("pinwindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("pinwindow", "N\303\244pp\303\244ile tunnusluku ja paina OK", nullptr));
        num1Button->setText(QCoreApplication::translate("pinwindow", "1", nullptr));
        num9Button->setText(QCoreApplication::translate("pinwindow", "9", nullptr));
        num7Button->setText(QCoreApplication::translate("pinwindow", "7", nullptr));
        num5Button->setText(QCoreApplication::translate("pinwindow", "5", nullptr));
        num6Button->setText(QCoreApplication::translate("pinwindow", "6", nullptr));
        num8Button->setText(QCoreApplication::translate("pinwindow", "8", nullptr));
        num3Button->setText(QCoreApplication::translate("pinwindow", "3", nullptr));
        num2Button->setText(QCoreApplication::translate("pinwindow", "2", nullptr));
        num4Button->setText(QCoreApplication::translate("pinwindow", "4", nullptr));
        num0Button->setText(QCoreApplication::translate("pinwindow", "0", nullptr));
        okButton->setText(QCoreApplication::translate("pinwindow", "OK", nullptr));
        clearButton->setText(QCoreApplication::translate("pinwindow", "CLEAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pinwindow: public Ui_pinwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINWINDOW_H
