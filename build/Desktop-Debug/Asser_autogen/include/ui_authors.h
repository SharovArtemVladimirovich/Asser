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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_authors
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *AuthorLabel;
    QPushButton *DonutButton;
    QPushButton *AuthorsBackMMButton;

    void setupUi(QWidget *authors)
    {
        if (authors->objectName().isEmpty())
            authors->setObjectName("authors");
        authors->resize(650, 850);
        authors->setMinimumSize(QSize(650, 850));
        horizontalLayout = new QHBoxLayout(authors);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(authors);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(631, 831));
        widget->setMaximumSize(QSize(631, 831));
        AuthorLabel = new QLabel(widget);
        AuthorLabel->setObjectName("AuthorLabel");
        AuthorLabel->setGeometry(QRect(0, 0, 631, 720));
        AuthorLabel->setMinimumSize(QSize(631, 720));
        AuthorLabel->setMaximumSize(QSize(631, 720));
        DonutButton = new QPushButton(widget);
        DonutButton->setObjectName("DonutButton");
        DonutButton->setGeometry(QRect(40, 740, 250, 70));
        AuthorsBackMMButton = new QPushButton(widget);
        AuthorsBackMMButton->setObjectName("AuthorsBackMMButton");
        AuthorsBackMMButton->setGeometry(QRect(340, 740, 250, 70));

        horizontalLayout->addWidget(widget);


        retranslateUi(authors);

        QMetaObject::connectSlotsByName(authors);
    } // setupUi

    void retranslateUi(QWidget *authors)
    {
        authors->setWindowTitle(QCoreApplication::translate("authors", "Form", nullptr));
        AuthorLabel->setText(QString());
        DonutButton->setText(QString());
        AuthorsBackMMButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class authors: public Ui_authors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORS_H
