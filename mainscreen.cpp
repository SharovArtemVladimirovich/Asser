#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "style.h"

#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QWindow>
#include <QMovie>

MainScreen::MainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreen)
{
    ui -> setupUi(this);
    ui -> widget -> setStyleSheet(MainScreenST::Style);

    connect(ui -> testButton, &QPushButton::clicked, this, &MainScreen::showTestsReq);
    connect(ui -> authorsButton, &QPushButton::clicked, this, &MainScreen::showAuthorsReq);
    connect(ui -> quitButton, &QPushButton::clicked, this, &MainScreen::quitButton_clicked);
    connect(ui -> manualsButton, &QPushButton::clicked, this, &MainScreen::showManualsReq);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::quitButton_clicked()
{
    class CustomDialog : public QDialog {
        public:
            CustomDialog(QWidget *parent = nullptr) : QDialog(parent, Qt::Dialog | Qt::WindowStaysOnTopHint) // Добавляем флаги
            {
                // Установка флагов окна
                setWindowFlags(windowFlags() |
                    Qt::CustomizeWindowHint |
                    Qt::WindowTitleHint |
                    Qt::WindowCloseButtonHint);// Последние настрйоки класса (Че тут к чему мне еще надо разобраться, но пока что да - так)

                QVBoxLayout *layoutV = new QVBoxLayout(this); // Обьявляем Лейаут для красотулечки ( V - значит ПОБЕДААААА ZZZZZ OOOOOO VVVVVV (verticale))
                QHBoxLayout *layoutH = new QHBoxLayout(this); // также объявляем, только теперь с H (вертолетная площадка)

                QLabel *labell = new QLabel(this); // Создаем лейбл (Ради которого я и переписывал весь msgBox в QDialog)
                labell -> setAlignment(Qt::AlignCenter); // Респределям его по центру

                //А вот и QMovie (Работает пизже и легче чем звук - я ебал )
                QMovie *movie = new QMovie(":/imagesDialog/gif/AsserQuitTxt.gif"); // Обьявлем под все добро переменную и суем в нее GIF из ресурсов
                labell -> setMovie(movie); // Пихаем наш Виджет QMovie с муви в лейбл
                movie -> start(); // Не забываем запустить

                QPushButton *noButton = new QPushButton(this); // Обьявляем кнопку НЕЕЕЕЕЕЕЕЕЕЕЕЕТ
                QPushButton *yesButton = new QPushButton(this);// ДААААААААААААААААААААААААААААААА

                    //Делаем из всего этого добра обьекты чтоб работать с ними в Стильном Листе
                noButton -> setObjectName("noButton");
                yesButton -> setObjectName("yesButton");
                labell -> setObjectName("labell");

                    // Работа с Лейаутами, чтобы все ровненько, красивенько, аккуратненько (Ахуеть, я их понял и познал - преисполнился в виджетах)
                layoutV -> addWidget(labell);  // в Вертикальный кидаем лейбл
                layoutH -> addWidget(noButton); // В горизонтальный пихаем две кнопки
                layoutH -> addWidget(yesButton);
                layoutV -> addLayout(layoutH); // Суем горизонтальный в вертикальный

                connect(noButton, &QPushButton::clicked, this, &QDialog::close); // Конектим кнопку на закрытие диалогового окна
                connect(yesButton, &QPushButton::clicked, this, &QApplication::quit); // На закрытие приложухи
            }
    };

    CustomDialog platon(this); // Явно указываем родительское окно!
    platon.setWindowModality(Qt::ApplicationModal); // Модальность приложения
    platon.setWindowTitle("Выйти (не в окно)"); // Для Диалога установим заголовок

    platon.setStyleSheet(MainScreenST::Dialog); // Ну и погнали описывать их в Стильном листе

    platon.exec(); // Ну и конечно же запускаем наше диалоговое окно и радуемся жизни!

}
