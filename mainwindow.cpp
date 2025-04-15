#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "authors.h"
#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QWindow>
#include <QMovie> // Библиотека для проигрования GIFвок

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Asser"); // Устанавливаем ттитульник сверху

    connect(ui -> ExitButton, &QPushButton::clicked, this, &MainWindow::ExitButton_clicked);//СОЕДИНЕНИЕ кнопки ВЫХОД
    connect(ui -> AuthorButton, &QPushButton::clicked, this, &MainWindow::AuthorButton_clicked); //Соединение кнопки АВТОРЫ
    connect(ui -> goFullScreenButton, &QPushButton::toggled, this, &MainWindow::goFullScreenButton_toggled); //переход в полноэкранный режим по кнопахе


    this->setWindowFlags((this->windowFlags() & ~Qt::WindowMaximizeButtonHint) | Qt::WindowMinimizeButtonHint); // Отключение возможности менять формат окна

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::GoTestButton_clicked() //Переход к разделам тестов
{

}


void MainWindow::GoStatButton_clicked() //Кнопка статистики
{

}


void MainWindow::GoDecoderButton_clicked() //Диз-ASS-емблер
{

}


void MainWindow::GoManualsButton_clicked() //Покурить маны
{

}


void MainWindow::AuthorButton_clicked() // о Рабах системы MS DOS
{
    Authors *authorsWindow = new Authors(); // Создаем окно, где родичь - МеинВиндоу
    authorsWindow -> setAttribute(Qt::WA_DeleteOnClose); //АвТоМаТиЧеСкОе УдАлЕнИе при закрытии
    authorsWindow->setWindowModality(Qt::ApplicationModal); // Делаем окно модальным
    authorsWindow -> show(); //Показ окна с авторами
}


void MainWindow::ExitButton_clicked() // Выход (Можно и в окно)
{
    class CustomDialog : public QDialog { // Обьявляем класс для диалогового окна (Замена --АСС-ажной коробке)

    public:
        CustomDialog(QWidget *parent = nullptr) : QDialog(parent) { // Последние настрйоки класса (Че тут к чему мне еще надо разобраться, но пока что да - так)

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
            layoutV->addWidget(labell);  // в Вертикальный кидаем лейбл
            layoutH->addWidget(noButton); // В горизонтальный пихаем две кнопки
            layoutH->addWidget(yesButton);
            layoutV->addLayout(layoutH); // Суем горизонтальный в вертикальный

            connect(noButton, &QPushButton::clicked, this, &QDialog::close); // Конектим кнопку на закрытие диалогового окна
            connect(yesButton, &QPushButton::clicked, this, &QApplication::quit); // На закрытие приложухи
        }
    };

    CustomDialog platon; // ДИАЛОГИ ТЕТ-А-ТЕТ ( Аж Мананникову вспомнил - снова заплакал )
    platon.setWindowTitle("Выйти в окно"); // Для Диалога установим заголовок

    platon.setStyleSheet( // Ну и погнали описывать их в Стильном листе
                        "QDialog {" // Для самого диалога
                        "      background-color: rgb(0,0,0);" // ставим цвет фона НИГЕР (Осуждаю)
                        "      color: white;" // цвет шрифта - господин фона
                        "      min-width: 530px;" // ограничиваем минимум по ширине
                        "      min-height: 230px;" // по высоте также
                        "}"

                        "QLabel#labell{" // Теперь описываем наш лейбл
                        "      max-width: 500px;" // теперь ограничиваем максимальные размеры (по ширине)
                        "      max-height: 40px;" // по высоте
                        "}"

                        // Общие настройки для кнопки
                        "QPushButton {"
                        "      max-width: 250px;" // Аналогичное ограничение
                        "      max-height: 50px;"
                        "      padding: 10px;" // а вот тут интересно: padding - это расстояние, которое обьект выделит себе вокруг и которую занять не смогут
                                               // Что то типо зоны вокруг обьект, не путать с margin - отступы внутри самого обьекта от кроев до содержания
                        "      border: none;"  // отключаем мерзкую обводку
                        "      outline: none;" // откулючаем мерзкую подсветку
                        "}"

                        // Задание картинок для НЕЕЕЕЕЕЕЕЕТ
                        "QPushButton#noButton{" // Ну тут в целом все по классике - почитайте ниже для goFullScreenButton_toggled, там я подробно расписал
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBNo.png);"
                        "}"

                        "QPushButton#noButton:hover{"
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBNo_hover.png);"
                        "}"

                        "QPushButton#noButton:pressed{"
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBNo_push.png);"
                        "}"

                        // Задание картинок для ДААААААААААА
                        "QPushButton#yesButton{"
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBYes.png);"
                        "}"

                        "QPushButton#yesButton:hover{"
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBYes_hover.png);"
                        "}"

                        "QPushButton#yesButton:pressed{"
                        "      image: url(:/imagesDialog/images/Asser_PB_quitBYes_push.png);"
                        "}"

                        );
    platon.exec(); // Ну и конечно же запускаем наше диалоговое окно и радуемся жизни!
}


void MainWindow::SettingsButton_clicked() // Настройки
{

}


void MainWindow::goFullScreenButton_toggled(bool checked) { //Прописываем функцию для нашей тоггл кнопочки ПОЛНОГО (Ну тип жирного, ага) экрана
    if (checked) { // Ну IF он и в Африке ГОЛОДНЫЙ
        m_previousGeometry = this->geometry(); // Устанавливаем для переменной значения для геометрии (Чтоб когда обратно вернулись все не померло)
        this->showFullScreen(); //Демонстрируем плебеям ЖИРНЫЙ (Ну тип полный, ага) экран

        //БЛЯДСКОЕ ЗАЛИПАНИЕ КЛАВИШ СТЕРЛА ВСЕ МОИ КОММЕНТЫ ТВАРЬ (пишу по новой - все для роднулек)

        ui->goFullScreenButton->setStyleSheet( // Теаерь открываем СтильныйЛист для нашей ГУИшки, чтоб все по красоте
            "#goFullScreenButton {" //Да да, именно для этой падлы
            "   border: none;" // Убираем стремную обводку, чтоб все было по красоте
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2.png);" //Пихаем картинку нашей кнопахи (для СУЖЕНИЯ)
            "   margin-bottom: 10px;" //Смещаем картинку вверх, так как сама кнопка растянута и надо будет потом картинку ОПУСКАТЬ вниз для предания эффекта
            "}"                       //смещения, а то я манал пилить физическое смещение (я уже говорил, что ненавижу залипание клавиш?)

            "#goFullScreenButton:hover {" // о, а теперь прописываем СТИЛЬНЫЙ ЛИСТ для состояния, когда мы навелись мышкой на кнопку
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2_hover.png);" // вот да - другая картинка
            "   margin-bottom: -10px;" // а вот и само "смещение" (просто убираем внутренний отступ кнопки и делаем эффект смещения)
            "}"

            "#goFullScreenButton:pressed {" // ну и наконец - состояние нажатой кнопахи
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2_push.png);"
            "   margin-bottom: -10px;" //не щелкаем еблом и ставим также смещение, так как margin-bottom: 10px;прописано для обычного состояния и является главным
            "}"
        );

    } else { // Ну ELSE он и в Африке ГОЛОДНЫЙ
        this->showNormal(); // Возвращаем ГУИшку к оконному виду
        this->setGeometry(m_previousGeometry); // пихаем ей нашу сохранённую геометрию
        ui->goFullScreenButton->setStyleSheet( // ну и дальше снова пропиываем для кнопахи стиль (Иначе он так и останется), только теперь с другой картинкой
            "#goFullScreenButton {"
            "   border: none;"
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen.png);"
            "   margin-bottom: 10px;"
            "}"

            "#goFullScreenButton:hover {"
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_hover.png);"
            "   margin-bottom: -10px;"
            "}"

            "#goFullScreenButton:pressed {"
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen_push.png);"
            "   margin-bottom: -10px;"
            "}"
        ); // Ну вот и пока что все (ебал я в рот залипание клавиш)
    }

}

