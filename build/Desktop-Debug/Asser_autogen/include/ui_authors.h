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
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authors
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *DonutButton;
    QPushButton *AuthorsBackMMButton;
    QPushButton *pushButton;
    QListView *listView;
    QLabel *label;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *Authors)
    {
        if (Authors->objectName().isEmpty())
            Authors->setObjectName("Authors");
        Authors->resize(668, 868);
        Authors->setMinimumSize(QSize(0, 0));
        Authors->setMaximumSize(QSize(668, 868));
        Authors->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(246, 245, 244);"));
        verticalLayout = new QVBoxLayout(Authors);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(Authors);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(40, 320, 531, 171));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 529, 169));
        DonutButton = new QPushButton(scrollAreaWidgetContents_2);
        DonutButton->setObjectName("DonutButton");
        DonutButton->setGeometry(QRect(50, 70, 187, 50));
        DonutButton->setMinimumSize(QSize(0, 50));
        DonutButton->setStyleSheet(QString::fromUtf8("color: rgb(224, 27, 36);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        AuthorsBackMMButton = new QPushButton(scrollAreaWidgetContents_2);
        AuthorsBackMMButton->setObjectName("AuthorsBackMMButton");
        AuthorsBackMMButton->setGeometry(QRect(30, 230, 187, 50));
        AuthorsBackMMButton->setMinimumSize(QSize(0, 50));
        AuthorsBackMMButton->setStyleSheet(QString::fromUtf8("color: rgb(224, 27, 36);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        pushButton = new QPushButton(scrollAreaWidgetContents_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(280, 400, 241, 101));
        listView = new QListView(scrollAreaWidgetContents_2);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(70, 530, 256, 192));
        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 100, 171, 17));
        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents_2);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(500, 0, 31, 171));
        verticalScrollBar->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 56, 70);"));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(widget);


        retranslateUi(Authors);

        QMetaObject::connectSlotsByName(Authors);
    } // setupUi

    void retranslateUi(QWidget *Authors)
    {
        Authors->setWindowTitle(QCoreApplication::translate("Authors", "Form", nullptr));
        DonutButton->setText(QCoreApplication::translate("Authors", "\320\235\320\260 \320\273\320\265\321\207\320\265\320\275\320\270\320\265 \320\262\321\213\321\210\320\265\321\203\320\277\320\276\320\274\321\217\320\275\321\203\321\202\321\213\321\205", nullptr));
        AuthorsBackMMButton->setText(QCoreApplication::translate("Authors", "\320\222\321\213\321\205\320\276\320\264 \320\262 \320\263\320\273\320\260\320\262\320\275\320\276\320\265\n"
"\320\274\320\265\320\275\321\216", nullptr));
        pushButton->setText(QCoreApplication::translate("Authors", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("Authors", "\320\233\320\270\321\201\321\202\320\260\320\271 \320\275\320\270\320\266\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authors: public Ui_Authors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORS_H
