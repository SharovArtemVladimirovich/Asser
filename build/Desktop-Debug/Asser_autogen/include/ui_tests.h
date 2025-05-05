/********************************************************************************
** Form generated from reading UI file 'tests.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTS_H
#define UI_TESTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tests
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widgetTests;
    QLabel *label;
    QPushButton *MainBackButton;
    QPushButton *goTestSeventhButton;
    QPushButton *goTestSixthButton;
    QPushButton *goTestFifthButton;
    QPushButton *goTestFourthButton;
    QPushButton *goTestThirdButton;
    QPushButton *goTestSecondButton;
    QPushButton *goTestFirstButton;

    void setupUi(QWidget *tests)
    {
        if (tests->objectName().isEmpty())
            tests->setObjectName("tests");
        tests->resize(650, 850);
        tests->setMinimumSize(QSize(650, 850));
        horizontalLayout = new QHBoxLayout(tests);
        horizontalLayout->setObjectName("horizontalLayout");
        widgetTests = new QWidget(tests);
        widgetTests->setObjectName("widgetTests");
        widgetTests->setMinimumSize(QSize(631, 832));
        widgetTests->setMaximumSize(QSize(631, 832));
        widgetTests->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(widgetTests);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 20, 401, 70));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainBackButton = new QPushButton(widgetTests);
        MainBackButton->setObjectName("MainBackButton");
        MainBackButton->setGeometry(QRect(40, 740, 550, 50));
        goTestSeventhButton = new QPushButton(widgetTests);
        goTestSeventhButton->setObjectName("goTestSeventhButton");
        goTestSeventhButton->setGeometry(QRect(40, 650, 550, 50));
        goTestSixthButton = new QPushButton(widgetTests);
        goTestSixthButton->setObjectName("goTestSixthButton");
        goTestSixthButton->setGeometry(QRect(40, 560, 550, 50));
        goTestFifthButton = new QPushButton(widgetTests);
        goTestFifthButton->setObjectName("goTestFifthButton");
        goTestFifthButton->setGeometry(QRect(40, 470, 550, 50));
        goTestFourthButton = new QPushButton(widgetTests);
        goTestFourthButton->setObjectName("goTestFourthButton");
        goTestFourthButton->setGeometry(QRect(40, 380, 550, 50));
        goTestFourthButton->setStyleSheet(QString::fromUtf8(""));
        goTestThirdButton = new QPushButton(widgetTests);
        goTestThirdButton->setObjectName("goTestThirdButton");
        goTestThirdButton->setGeometry(QRect(40, 290, 550, 50));
        goTestSecondButton = new QPushButton(widgetTests);
        goTestSecondButton->setObjectName("goTestSecondButton");
        goTestSecondButton->setGeometry(QRect(40, 200, 550, 50));
        goTestFirstButton = new QPushButton(widgetTests);
        goTestFirstButton->setObjectName("goTestFirstButton");
        goTestFirstButton->setGeometry(QRect(40, 110, 550, 50));

        horizontalLayout->addWidget(widgetTests);


        retranslateUi(tests);

        QMetaObject::connectSlotsByName(tests);
    } // setupUi

    void retranslateUi(QWidget *tests)
    {
        tests->setWindowTitle(QCoreApplication::translate("tests", "Form", nullptr));
        label->setText(QString());
        MainBackButton->setText(QString());
        goTestSeventhButton->setText(QString());
        goTestSixthButton->setText(QString());
        goTestFifthButton->setText(QString());
        goTestFourthButton->setText(QString());
        goTestThirdButton->setText(QString());
        goTestSecondButton->setText(QString());
        goTestFirstButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tests: public Ui_tests {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTS_H
