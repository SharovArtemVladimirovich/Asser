/********************************************************************************
** Form generated from reading UI file 'authors.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORS_H
#define UI_AUTHORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authors
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *DonutButton;
    QPushButton *AuthorsBackMMButton;

    void setupUi(QWidget *Authors)
    {
        if (Authors->objectName().isEmpty())
            Authors->setObjectName("Authors");
        Authors->resize(550, 650);
        Authors->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(246, 245, 244);"));
        label = new QLabel(Authors);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 50, 131, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(38, 162, 105);"));
        label_2 = new QLabel(Authors);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 120, 321, 51));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(true);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(38, 162, 105);"));
        label_3 = new QLabel(Authors);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 190, 321, 51));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(38, 162, 105);"));
        label_4 = new QLabel(Authors);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 260, 371, 51));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(38, 162, 105);"));
        DonutButton = new QPushButton(Authors);
        DonutButton->setObjectName("DonutButton");
        DonutButton->setGeometry(QRect(60, 490, 201, 81));
        DonutButton->setStyleSheet(QString::fromUtf8("color: rgb(224, 27, 36);"));
        AuthorsBackMMButton = new QPushButton(Authors);
        AuthorsBackMMButton->setObjectName("AuthorsBackMMButton");
        AuthorsBackMMButton->setGeometry(QRect(280, 490, 201, 81));
        AuthorsBackMMButton->setStyleSheet(QString::fromUtf8("color: rgb(224, 27, 36);\n"
"border-color: rgb(224, 27, 36);\n"
"border: 3px;\n"
""));

        retranslateUi(Authors);

        QMetaObject::connectSlotsByName(Authors);
    } // setupUi

    void retranslateUi(QWidget *Authors)
    {
        Authors->setWindowTitle(QCoreApplication::translate("Authors", "Form", nullptr));
        label->setText(QCoreApplication::translate("Authors", "\320\220\320\262\321\202\320\276\321\200\321\213:", nullptr));
        label_2->setText(QCoreApplication::translate("Authors", "\320\241\321\203\320\265\321\202\320\270\320\275 \320\230\320\273\321\214\321\217 \320\224\320\274\320\270\321\202\321\200\320\270\320\265\320\262\320\270\321\207", nullptr));
        label_3->setText(QCoreApplication::translate("Authors", "\320\250\320\260\321\200\320\276\320\262 \320\220\321\200\321\202\321\221\320\274 \320\222\320\273\320\260\320\264\320\270\320\274\320\270\321\200\320\276\320\262\320\270\321\207", nullptr));
        label_4->setText(QCoreApplication::translate("Authors", "\320\221\321\203\321\202\320\265\320\275\320\272\320\276 \320\225\320\273\320\270\320\267\320\260\320\262\320\265\321\202\320\260 \320\220\320\275\320\264\321\200\320\265\320\265\320\262\320\275\320\260", nullptr));
        DonutButton->setText(QCoreApplication::translate("Authors", "\320\235\320\260 \320\273\320\265\321\207\320\265\320\275\320\270\320\265 \320\262\321\213\321\210\320\265\321\203\320\277\320\276\320\274\321\217\320\275\321\203\321\202\321\213\321\205", nullptr));
        AuthorsBackMMButton->setText(QCoreApplication::translate("Authors", "\320\222\321\213\321\205\320\276\320\264 \320\262 \320\263\320\273\320\260\320\262\320\275\320\276\320\265\n"
"\320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authors: public Ui_Authors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORS_H
