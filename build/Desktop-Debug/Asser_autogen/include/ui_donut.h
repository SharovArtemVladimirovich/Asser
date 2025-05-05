/********************************************************************************
** Form generated from reading UI file 'donut.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DONUT_H
#define UI_DONUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Donut
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QPushButton *goBackToAuthorsButton;

    void setupUi(QWidget *Donut)
    {
        if (Donut->objectName().isEmpty())
            Donut->setObjectName("Donut");
        Donut->resize(650, 850);
        Donut->setMinimumSize(QSize(650, 850));
        horizontalLayout = new QHBoxLayout(Donut);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(Donut);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(631, 831));
        goBackToAuthorsButton = new QPushButton(widget);
        goBackToAuthorsButton->setObjectName("goBackToAuthorsButton");
        goBackToAuthorsButton->setGeometry(QRect(340, 740, 250, 70));
        goBackToAuthorsButton->setMinimumSize(QSize(250, 70));

        horizontalLayout->addWidget(widget);


        retranslateUi(Donut);

        QMetaObject::connectSlotsByName(Donut);
    } // setupUi

    void retranslateUi(QWidget *Donut)
    {
        Donut->setWindowTitle(QCoreApplication::translate("Donut", "Form", nullptr));
        goBackToAuthorsButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Donut: public Ui_Donut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DONUT_H
