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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
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
    QLabel *label;
    QPushButton *goFullScreenButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(650, 850);
        MainWindow->setMinimumSize(QSize(650, 850));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(650, 806));
        centralwidget->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        centralwidget->setAutoFillBackground(false);
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        GoTestButton = new QPushButton(centralwidget);
        GoTestButton->setObjectName("GoTestButton");
        GoTestButton->setGeometry(QRect(300, 280, 321, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("FreeMono")});
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        GoTestButton->setFont(font);
        GoTestButton->setTabletTracking(true);
        GoTestButton->setStyleSheet(QString::fromUtf8("#GoTestButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\242\320\265\321\201\321\202\321\213.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#GoTestButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\242\320\265\321\201\321\202\321\213_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#GoTestButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\242\320\265\321\201\321\202\321\213_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        GoTestButton->setCheckable(false);
        GoStatButton = new QPushButton(centralwidget);
        GoStatButton->setObjectName("GoStatButton");
        GoStatButton->setGeometry(QRect(300, 360, 321, 51));
        GoStatButton->setTabletTracking(true);
        GoStatButton->setStyleSheet(QString::fromUtf8("#GoStatButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#GoStatButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#GoStatButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        GoDecoderButton = new QPushButton(centralwidget);
        GoDecoderButton->setObjectName("GoDecoderButton");
        GoDecoderButton->setGeometry(QRect(300, 440, 321, 51));
        GoDecoderButton->setTabletTracking(true);
        GoDecoderButton->setStyleSheet(QString::fromUtf8("#GoDecoderButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\224\320\270\320\267\320\260\321\201\321\201\320\265\320\274\320\261\320\273\320\265\321\200.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#GoDecoderButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\224\320\270\320\267\320\260\321\201\321\201\320\265\320\274\320\261\320\273\320\265\321\200_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#GoDecoderButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\224\320\270\320\267\320\260\321\201\321\201\320\265\320\274\320\261\320\273\320\265\321\200_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        GoManualsButton = new QPushButton(centralwidget);
        GoManualsButton->setObjectName("GoManualsButton");
        GoManualsButton->setGeometry(QRect(300, 520, 321, 51));
        GoManualsButton->setTabletTracking(true);
        GoManualsButton->setStyleSheet(QString::fromUtf8("#GoManualsButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\234\320\260\320\275\321\203\320\260\320\273\321\213.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#GoManualsButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\234\320\260\320\275\321\203\320\260\320\273\321\213_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#GoManualsButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\234\320\260\320\275\321\203\320\260\320\273\321\213_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        AuthorButton = new QPushButton(centralwidget);
        AuthorButton->setObjectName("AuthorButton");
        AuthorButton->setGeometry(QRect(300, 600, 321, 51));
        AuthorButton->setTabletTracking(true);
        AuthorButton->setStyleSheet(QString::fromUtf8("#AuthorButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\236\320\261\320\220\320\262\321\202\320\276\321\200\320\260\321\205.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#AuthorButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\236\320\261\320\220\320\262\321\202\320\276\321\200\320\260\321\205_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#AuthorButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\236\320\261\320\220\320\262\321\202\320\276\321\200\320\260\321\205_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        ExitButton = new QPushButton(centralwidget);
        ExitButton->setObjectName("ExitButton");
        ExitButton->setGeometry(QRect(300, 680, 321, 51));
        ExitButton->setTabletTracking(true);
        ExitButton->setStyleSheet(QString::fromUtf8("#ExitButton {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\222\321\213\321\205\320\276\320\264.png);\n"
"	margin-left: 20px;\n"
"	border: none;\n"
"    outline: none;\n"
"}\n"
"#ExitButton:hover {\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\222\321\213\321\205\320\276\320\264_hover.png);\n"
"	margin-left: -20px;\n"
"}\n"
"#ExitButton:pressed{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_\320\222\321\213\321\205\320\276\320\264_push.png);\n"
"	margin-left: -20px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/Asser_PB_\320\222\321\213\321\205\320\276\320\264.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ExitButton->setIcon(icon);
        ExitButton->setIconSize(QSize(300, 50));
        SettingsButton = new QPushButton(centralwidget);
        SettingsButton->setObjectName("SettingsButton");
        SettingsButton->setGeometry(QRect(560, 20, 41, 51));
        SettingsButton->setStyleSheet(QString::fromUtf8("#SettingsButton{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_Settings.png);\n"
"	border: none;\n"
"    outline: none;\n"
"	margin-bottom: 10px;\n"
"}\n"
"\n"
"#SettingsButton:hover{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_Settings_hover.png);\n"
"	margin-bottom: -10px;\n"
"}\n"
"\n"
"#SettingsButton:pressed{	\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_Settings_push.png);\n"
"	margin-bottom: -10px;\n"
"}"));
        SettingsButton->setIconSize(QSize(30, 30));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 80, 391, 151));
        label->setStyleSheet(QString::fromUtf8("#label {\n"
"image: url(:/imagesMainMenuLogo/images/Asser_Turbo_logo1.png);\n"
"}"));
        label->setMidLineWidth(2);
        goFullScreenButton = new QPushButton(centralwidget);
        goFullScreenButton->setObjectName("goFullScreenButton");
        goFullScreenButton->setGeometry(QRect(510, 20, 41, 51));
        goFullScreenButton->setStyleSheet(QString::fromUtf8("#goFullScreenButton{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen.png);\n"
"	border: none;\n"
"    outline: none;\n"
"	margin-bottom: 10px;\n"
"}\n"
"\n"
"#goFullScreenButton:hover{\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_hover.png);\n"
"	margin-bottom: -10px;\n"
"}\n"
"\n"
"#goFullScreenButton:pressed{\n"
"	\n"
"	image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_push.png);\n"
"	margin-bottom: -10px;\n"
"}"));
        goFullScreenButton->setIconSize(QSize(30, 30));
        goFullScreenButton->setCheckable(true);
        MainWindow->setCentralWidget(centralwidget);
        label->raise();
        GoTestButton->raise();
        GoStatButton->raise();
        GoDecoderButton->raise();
        GoManualsButton->raise();
        AuthorButton->raise();
        ExitButton->raise();
        SettingsButton->raise();
        goFullScreenButton->raise();
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
        GoTestButton->setText(QString());
        GoStatButton->setText(QString());
        GoDecoderButton->setText(QString());
        GoManualsButton->setText(QString());
        AuthorButton->setText(QString());
        ExitButton->setText(QString());
        SettingsButton->setText(QString());
        label->setText(QString());
        goFullScreenButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
