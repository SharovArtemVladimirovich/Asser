#ifndef STYLE_H
#define STYLE_H

#pragma once

#include <QString>


namespace GlobalST {
    const QString Background = R"(
            QMainWindow {
                background-image: url(:/imagesMainMenu/images/Asser_background.png);
                background-position: center;
                background-repeat: no-repeat;
                background-attachment: fixed;
            }
    )";
    const QString FSButton = R"(

        QPushButton {
            border: none;
            outline: none;
        }

        QPushButton#fullscreenBtn {
            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen.png);
            margin-bottom: 10px;
        }
        QPushButton#fullscreenBtn:hover{
            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_hover.png);
            margin-bottom: -10px;
        }
        QPushButton#fullscreenBtn:pressed{

            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_push.png);
            margin-bottom: -10px;
        }


        QPushButton#fullscreenBtn:checked {
            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2.png);
            margin-bottom: 10px;
        }
        QPushButton#fullscreenBtn:checked:hover{
            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2_hover.png);
            margin-bottom: -10px;
        }
        QPushButton#fullscreenBtn:checked:pressed{

            image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2_push.png);
            margin-bottom: -10px;
        }

    )";
}
namespace MainScreenST {
    const QString Style = R"(
        QWidget#widget {
        background-color: rgb(0, 0, 0);
            border: none;
            outline: none;
        }
        QPushButton {
            border: none;
            outline: none;
        }


        QPushButton#testButton {
            image: url(:/imagesMainMenu/images/Asser_PB_Тесты.png);
            margin-left: 20px;
        }
        QPushButton#testButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_Тесты_hover.png);
            margin-left: -20px;
        }
        QPushButton#testButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_Тесты_push.png);
            margin-left: -20px;
        }


        QPushButton#statButton {
            image: url(:/imagesMainMenu/images/Asser_PB_Статистика.png);
            margin-left: 20px;
        }
        QPushButton#statButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_Статистика_hover.png);
            margin-left: -20px;
        }
        QPushButton#statButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_Статистика_push.png);
            margin-left: -20px;
        }


        QPushButton#decodeButton {
            image: url(:/imagesMainMenu/images/Asser_PB_Дизассемблер.png);
            margin-left: 20px;
        }
        QPushButton#decodeButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_Дизассемблер_hover.png);
            margin-left: -20px;
        }
        QPushButton#decodeButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_Дизассемблер_push.png);
            margin-left: -20px;
        }


        QPushButton#manualsButton {
            image: url(:/imagesMainMenu/images/Asser_PB_Мануалы.png);
            margin-left: 20px;
        }
        QPushButton#manualsButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_Мануалы_hover.png);
            margin-left: -20px;
        }
        QPushButton#manualsButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_Мануалы_push.png);
            margin-left: -20px;
        }


        QPushButton#authorsButton {
            image: url(:/imagesMainMenu/images/Asser_PB_ОбАвторах.png);
            margin-left: 20px;
        }
        QPushButton#authorsButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_ОбАвторах_hover.png);
            margin-left: -20px;
        }
        QPushButton#authorsButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_ОбАвторах_push.png);
            margin-left: -20px;
        }


        QPushButton#quitButton {
            image: url(:/imagesMainMenu/images/Asser_PB_Выход.png);
            margin-left: 20px;
        }
        QPushButton#quitButton:hover {
            image: url(:/imagesMainMenu/images/Asser_PB_Выход_hover.png);
            margin-left: -20px;
        }
        QPushButton#quitButton:pressed{
            image: url(:/imagesMainMenu/images/Asser_PB_Выход_push.png);
            margin-left: -20px;
        }


        QLabel#label {
            image: url(:/imagesMainMenuLogo/images/Asser_Turbo_logo1.png);
        }


    )";

    const QString Dialog = R"(
        QDialog {
            background-color: rgb(0,0,0);
            color: white;
            min-width: 530px;
            min-height: 230px;
        }

        QLabel#labell {
            max-width: 500px;
            max-height: 40px;
        }

        QPushButton {
            max-width: 250px;
            max-height: 50px;
            padding: 10px;
            border: none;
            outline: none;
        }

        QPushButton#noButton {
            image: url(:/imagesDialog/images/Asser_PB_quitBNo.png);
        }

        QPushButton#noButton:hover {
            image: url(:/imagesDialog/images/Asser_PB_quitBNo_hover.png);
        }

        QPushButton#noButton:pressed {
            image: url(:/imagesDialog/images/Asser_PB_quitBNo_push.png);
        }

        QPushButton#yesButton {
            image: url(:/imagesDialog/images/Asser_PB_quitBYes.png);
        }

        QPushButton#yesButton:hover {
            image: url(:/imagesDialog/images/Asser_PB_quitBYes_hover.png);
        }

        QPushButton#yesButton:pressed {
            image: url(:/imagesDialog/images/Asser_PB_quitBYes_push.png);
        }
    )";
}
namespace TestsST {
    const QString StyleT = R"(
        QWidget#widgetTests {
            background-color: rgb(0,0,0);
        }

        QLabel#label {
            image: url(:/imagesTests/images/Asser_Turbo_logo_Tests.png);
            background-color: rgb(0,0,0);
        }

        QPushButton{
            border: none;
            outline: none;
        }

        QPushButton#goTestFirstButton {
            image: url(:/imagesTests/images/Asser_TPB_1.png);
        }
        QPushButton#goTestFirstButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_1_hover.png);
        }
        QPushButton#goTestFirstButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_1_push.png);
        }


        QPushButton#goTestSecondButton {
            image: url(:/imagesTests/images/Asser_TPB_2.png);
        }
        QPushButton#goTestSecondButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_2_hover.png);
        }
        QPushButton#goTestSecondButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_2_push.png);
        }


        QPushButton#goTestThirdButton {
            image: url(:/imagesTests/images/Asser_TPB_3.png);
        }
        QPushButton#goTestThirdButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_3_hover.png);
        }
        QPushButton#goTestThirdButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_3_push.png);
        }


        QPushButton#goTestFourthButton {
            image: url(:/imagesTests/images/Asser_TPB_4.png);
        }
        QPushButton#goTestFourthButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_4_hover.png);
        }
        QPushButton#goTestFourthButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_4_push.png);
        }


        QPushButton#goTestFifthButton {
            image: url(:/imagesTests/images/Asser_TPB_5.png);
        }
        QPushButton#goTestFifthButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_5_hover.png);
        }
        QPushButton#goTestFifthButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_5_push.png);
        }


        QPushButton#goTestSeventhButton {
            image: url(:/imagesTests/images/Asser_TPB_7.png);
        }
        QPushButton#goTestSeventhButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_7_hover.png);
        }
        QPushButton#goTestSeventhButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_7_push.png);
        }


        QPushButton#goTestEighthButton {
            image: url(:/imagesTests/images/Asser_TPB_8.png);
        }
        QPushButton#goTestEighthButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_8_hover.png);
        }
        QPushButton#goTestEighthButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_8_push.png);
        }


        QPushButton#MainBackButton {
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu.png);
        }
        QPushButton#MainBackButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu_hover.png);
        }
        QPushButton#MainBackButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu_push.png);
        }
    )";
}
namespace AuthorsST {
    const QString StyleA = R"(

        QPushButton{
            border: none;
            outline: none;
        }

        QPushButton#AuthorsBackMMButton {
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu.png);
            margin-top: 10px;
        }
        QPushButton#AuthorsBackMMButton:hover {
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu_hover.png);
            margin-top: -10px;
        }
        QPushButton#AuthorsBackMMButton:pressed{
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu_push.png);
            margin-top: -10px;
        }

        QPushButton#DonutButton {
            image: url(:/imagesAuthors/images/Asser_APB_donut.png);
            margin-top: 10px;
        }
        QPushButton#DonutButton:hover {
            image: url(:/imagesAuthors/images/Asser_APB_donut_hover.png);
            margin-top: -10px;
        }
        QPushButton#DonutButton:pressed{
            image: url(:/imagesAuthors/images/Asser_APB_donut_push.png);
            margin-top: -10px;
        }
    )";
}
namespace DonutST {
    const QString StyleD = R"(

        QPushButton{
            border: none;
            outline: none;
        }

        QPushButton#goBackToAuthorsButton {
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu.png);
            margin-top: 10px;
        }
        QPushButton#goBackToAuthorsButton:hover {
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu_hover.png);
            margin-top: -10px;
        }
        QPushButton#goBackToAuthorsButton:pressed{
            image: url(:/imagesAuthors/images/Asser_APB_BackToMenu_push.png);
            margin-top: -10px;
        }
    )";
}
namespace ManualsST {
    const QString StyleM = R"(

        QPushButton{
            border: none;
            outline: none;
        }

        QLabel#label{
            image: url(:/imagesManuals/images/Asser_ML.png);
        }

        QPushButton#MainBackButton {
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu.png);
        }
        QPushButton#MainBackButton:hover {
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu_hover.png);
        }
        QPushButton#MainBackButton:pressed{
            image: url(:/imagesTests/images/Asser_TPB_BackToMenu_push.png);
        }

        QPushButton#intelDocsButton {
            image: url(:/imagesManuals/images/Asser_MPB_IntelDocs.png);
        }
        QPushButton#intelDocsButton:hover {
            image: url(:/imagesManuals/images/Asser_MPB_IntelDocs_hover.png);
        }
        QPushButton#intelDocsButton:pressed{
            image: url(:/imagesManuals/images/Asser_MPB_IntelDocs_push.png);
        }

        QPushButton#assemblyTutorialButton {
            image: url(:/imagesManuals/images/Asser_MPB_AssBook.png);
        }
        QPushButton#assemblyTutorialButton:hover {
            image: url(:/imagesManuals/images/Asser_MPB_AssBook_hover.png);
        }
        QPushButton#assemblyTutorialButton:pressed{
            image: url(:/imagesManuals/images/Asser_MPB_AssBook_push.png);
        }

        QPushButton#downloadCheatsheetButton {
            image: url(:/imagesManuals/images/Asser_MPB_Shpora.png);
        }
        QPushButton#downloadCheatsheetButton:hover {
            image: url(:/imagesManuals/images/Asser_MPB_Shpora_hover.png);
        }
        QPushButton#downloadCheatsheetButton:pressed{
            image: url(:/imagesManuals/images/Asser_MPB_Shpora_push.png);
        }
    )";
}
namespace TestsDialogST {
    const QString StyleTD = R"(

)";
    const QString Opisanie = R"(
    Добро пожаловать на бойню!
Здесь нет мамки с папкой, нет друзей и товарищей.
Только ты и ассемблер - больше ничего!
)";
}

#endif // STYLE_H
