#include "tests.h"
#include "ui_tests.h"
#include "mainwindow.h"
#include "style.h"
#include "starttestdialog.h"

#include <QFile>
tests::tests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tests)
{
    ui -> setupUi(this);
    setupTestButtons();
    ui -> widgetTests -> setStyleSheet (TestsST::StyleT);

    connect(ui -> MainBackButton, &QPushButton::clicked, this, &tests::showMainReq);
}

void tests::setupTestButtons() {
    // Предположим, кнопки названы buttonTest1..buttonTest7
    testButtons = {
        ui -> goTestFirstButton, ui -> goTestSecondButton, ui -> goTestThirdButton,
        ui -> goTestFourthButton, ui -> goTestFifthButton, ui -> goTestSeventhButton, ui -> goTestEighthButton
    };

    // Соответствие кнопок типам тестов
    testTypes = {
        TestType::SystemSch,
        TestType::Mov,
        TestType::Arifmetic,
        TestType::Logic,
        TestType::Stack,
        TestType::Coding,
        TestType::Decoding
    };

    for (int i = 0; i < testButtons.size(); ++i) {
            connect(testButtons[i], &QPushButton::clicked, [this, i]() {
                // Получите название теста по TestType
                QString testName;
                switch (i){
                case (0):
                    testName = "Системы счисления и преобразования данных";
                    break;
                case (1):
                    testName = "Режимы адресации. Команда MOV";
                    break;
                case (2):
                    testName = "Команды арифметики и работы с памятью";
                    break;
                case (3):
                    testName = "Команды логики и сдвигов";
                    break;
                case (4):
                    testName = "Команды работы со стеком";
                    break;
                case (5):
                    testName = "Ассемблирование команд";
                    break;
                case (6):
                    testName = "Дизассемблирование команд";
                    break;
                }

                // Передайте название в конструктор
                StartTestDialog dialog(this, testName);

                if (dialog.exec() == QDialog::Accepted) {
                    emit testRequested(testTypes[i], dialog.userName(), dialog.selectedVariant());
                }
            });
        }
}



tests::~tests()
{
    delete ui;
}
