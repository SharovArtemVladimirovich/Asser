/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QPushButton *testButton;
    QPushButton *statButton;
    QPushButton *decodeButton;
    QPushButton *manualsButton;
    QPushButton *authorsButton;
    QPushButton *quitButton;
    QLabel *label;

    void setupUi(QWidget *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName("MainScreen");
        MainScreen->resize(650, 850);
        MainScreen->setMinimumSize(QSize(650, 850));
        MainScreen->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        horizontalLayout = new QHBoxLayout(MainScreen);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(MainScreen);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(632, 832));
        widget->setMaximumSize(QSize(632, 832));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 100);"));
        testButton = new QPushButton(widget);
        testButton->setObjectName("testButton");
        testButton->setGeometry(QRect(280, 240, 321, 51));
        testButton->setMinimumSize(QSize(321, 51));
        statButton = new QPushButton(widget);
        statButton->setObjectName("statButton");
        statButton->setGeometry(QRect(280, 340, 321, 51));
        statButton->setMinimumSize(QSize(321, 51));
        decodeButton = new QPushButton(widget);
        decodeButton->setObjectName("decodeButton");
        decodeButton->setGeometry(QRect(280, 440, 321, 51));
        decodeButton->setMinimumSize(QSize(321, 51));
        manualsButton = new QPushButton(widget);
        manualsButton->setObjectName("manualsButton");
        manualsButton->setGeometry(QRect(280, 540, 321, 51));
        manualsButton->setMinimumSize(QSize(321, 51));
        authorsButton = new QPushButton(widget);
        authorsButton->setObjectName("authorsButton");
        authorsButton->setGeometry(QRect(280, 640, 321, 51));
        authorsButton->setMinimumSize(QSize(321, 51));
        quitButton = new QPushButton(widget);
        quitButton->setObjectName("quitButton");
        quitButton->setGeometry(QRect(280, 740, 321, 51));
        quitButton->setMinimumSize(QSize(321, 51));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 50, 390, 126));

        horizontalLayout->addWidget(widget);


        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QWidget *MainScreen)
    {
        MainScreen->setWindowTitle(QCoreApplication::translate("MainScreen", "Form", nullptr));
        testButton->setText(QString());
        statButton->setText(QString());
        decodeButton->setText(QString());
        manualsButton->setText(QString());
        authorsButton->setText(QString());
        quitButton->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
