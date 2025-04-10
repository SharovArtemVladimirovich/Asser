/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *GoTestButton;
    QPushButton *GoStatButton;
    QPushButton *GoDecoderButton;
    QPushButton *GoManualsButton;
    QPushButton *AuthorButton;
    QPushButton *ExitButton;
    QPushButton *SettingsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(650, 850);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        GoTestButton = new QPushButton(centralwidget);
        GoTestButton->setObjectName("GoTestButton");
        GoTestButton->setGeometry(QRect(320, 290, 301, 51));
        GoTestButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        GoStatButton = new QPushButton(centralwidget);
        GoStatButton->setObjectName("GoStatButton");
        GoStatButton->setGeometry(QRect(320, 370, 301, 51));
        GoStatButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        GoDecoderButton = new QPushButton(centralwidget);
        GoDecoderButton->setObjectName("GoDecoderButton");
        GoDecoderButton->setGeometry(QRect(320, 450, 301, 51));
        GoDecoderButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        GoManualsButton = new QPushButton(centralwidget);
        GoManualsButton->setObjectName("GoManualsButton");
        GoManualsButton->setGeometry(QRect(320, 530, 301, 51));
        GoManualsButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        AuthorButton = new QPushButton(centralwidget);
        AuthorButton->setObjectName("AuthorButton");
        AuthorButton->setGeometry(QRect(320, 610, 301, 51));
        AuthorButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName("ExitButton");
        ExitButton->setGeometry(QRect(320, 690, 301, 51));
        ExitButton->setStyleSheet(QString::fromUtf8("color: rgb(246, 245, 244);\n"
"font: 800 italic 14pt \"Fira Sans\";\n"
"background-color: rgb(36, 31, 49);"));
        SettingsButton = new QPushButton(centralwidget);
        SettingsButton->setObjectName("SettingsButton");
        SettingsButton->setGeometry(QRect(560, 0, 61, 61));
        SettingsButton->setStyleSheet(QString::fromUtf8("background-color: rgb(36, 31, 49);\n"
"color: rgb(246, 245, 244);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 650, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        GoTestButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273\321\213 \321\202\320\265\321\201\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        GoStatButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        GoDecoderButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\267\320\260\321\201\321\201\320\265\320\274\320\261\320\273\320\265\321\200", nullptr));
        GoManualsButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        AuthorButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261 \320\260\320\262\321\202\320\276\321\200\320\260\321\205", nullptr));
        ExitButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        SettingsButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
