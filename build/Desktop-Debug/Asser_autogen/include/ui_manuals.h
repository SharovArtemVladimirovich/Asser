/********************************************************************************
** Form generated from reading UI file 'manuals.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALS_H
#define UI_MANUALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Manuals
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QPushButton *intelDocsButton;
    QPushButton *assemblyTutorialButton;
    QPushButton *downloadCheatsheetButton;
    QPushButton *MainBackButton;
    QLabel *label;

    void setupUi(QWidget *Manuals)
    {
        if (Manuals->objectName().isEmpty())
            Manuals->setObjectName("Manuals");
        Manuals->resize(650, 850);
        Manuals->setMinimumSize(QSize(650, 850));
        horizontalLayout = new QHBoxLayout(Manuals);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(Manuals);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(631, 831));
        widget->setMaximumSize(QSize(631, 831));
        intelDocsButton = new QPushButton(widget);
        intelDocsButton->setObjectName("intelDocsButton");
        intelDocsButton->setGeometry(QRect(40, 470, 550, 50));
        assemblyTutorialButton = new QPushButton(widget);
        assemblyTutorialButton->setObjectName("assemblyTutorialButton");
        assemblyTutorialButton->setGeometry(QRect(40, 560, 550, 50));
        downloadCheatsheetButton = new QPushButton(widget);
        downloadCheatsheetButton->setObjectName("downloadCheatsheetButton");
        downloadCheatsheetButton->setGeometry(QRect(40, 650, 550, 50));
        MainBackButton = new QPushButton(widget);
        MainBackButton->setObjectName("MainBackButton");
        MainBackButton->setGeometry(QRect(40, 740, 550, 50));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 0, 450, 450));

        horizontalLayout->addWidget(widget);


        retranslateUi(Manuals);

        QMetaObject::connectSlotsByName(Manuals);
    } // setupUi

    void retranslateUi(QWidget *Manuals)
    {
        Manuals->setWindowTitle(QCoreApplication::translate("Manuals", "Form", nullptr));
        intelDocsButton->setText(QString());
        assemblyTutorialButton->setText(QString());
        downloadCheatsheetButton->setText(QString());
        MainBackButton->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Manuals: public Ui_Manuals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALS_H
