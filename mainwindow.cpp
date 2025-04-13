#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "authors.h"
#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Asser");

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


void MainWindow::GoDecoderButton_clicked() //Дизассемблер
{

}


void MainWindow::GoManualsButton_clicked() //Покурить маны
{

}


void MainWindow::AuthorButton_clicked() // о Рабах системы MS DOS
{
    Authors *authorsWindow = new Authors(); // Создаем окно, где родичь - МеинВиндоу
    authorsWindow -> setAttribute(Qt::WA_DeleteOnClose); //АвТоМаТиЧеСкОе УдАлЕнИе при закрытии
    authorsWindow -> show(); //Показ окна с авторами
}


void MainWindow::ExitButton_clicked() // Выход (Можно и в окно)
{
    QMessageBox msgBox(this); //прописываем создание Массажной коробки
    msgBox.setWindowTitle("Выйти в окно"); // Для массажной коробки установим заголовок
    msgBox.setText("Ты точно уверен в этом?"); //вывод текста в массажную коробку
    QPushButton* yesButton = msgBox.addButton(QMessageBox::Yes); //задаем тама кнопку ДА
    QPushButton* noButton = msgBox.addButton(QMessageBox::No); // аналогично задаем кнопку НЕТ
    yesButton -> setText("Да, отчисляйте"); //ну тут текст для кнопок в Коробковом массаже (ДА)
    noButton -> setText("Нет, простите"); // также и для НЕТ
    msgBox.exec(); //Че то типо запуска нашего Массажного Коробка
    if (msgBox.clickedButton() == yesButton) { //проверка на то, нажата ли кнопка ДА в массажном боксе (обращение к классу msgBox свойству clickedButton() )
        QApplication::quit(); // Закрываем ВСЁ ПРИЛОЖЕНИЕ (Ебучий костыль исправлен)
    }
}


void MainWindow::SettingsButton_clicked() // Настройки
{

}


void MainWindow::goFullScreenButton_toggled(bool checked) { //Прописываем функцию для нашей тоггл кнопочки ПОЛНОГО (Ну тип жирного, ага) экрана
    if (checked) { // Ну IF он и в Африке ГОЛОДНЫЙ
        m_previousGeometry = this->geometry(); // Устанавливаем для переменной значения для геометрии (Чтоб когда обратно вернулись все не померло)
        this->showFullScreen(); //Демонстрируем плебеям ЖИРНЫЙ (Ну тип жирного, ага)

        //БЛЯДСКОЕ ЗАЛИПАНИЕ КЛАВИШ СТЕРЛА ВСЕ МОИ КОММЕНТЫ ТВАРЬ (пишу по новой - все для роднулек)

        ui->goFullScreenButton->setStyleSheet( // Теаерь открываем СтильныйЛист для нашей ГУИшки, чтоб все по красоте
            "#goFullScreenButton {" //Да да, именно для этой падлы
            "   border: none;" // Убираем стремную обводку, чтоб все было по красоте
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2.png);" //Пихаем картинку нашей кнопахи (для СУЖЕНИЯ)
            "   margin-bottom: 10px;" //Смещаем картинку вверх, так как сама кнопка растянута и надо будет потом картинку ОПУСКАТЬ вниз для предания эффекта
            "}"                       //смещения, а то я манал пилить физическое смещение (я уже говорил, что ненавижу залипание клавиш?)

            "#goFullScreenButton:hover {" // о, а теперь прописываем СТИЛЬНЫЙ ЛИСТ для состояния, когда мы навелись мышкой на кнопку
            "   image: url(:/imagesMainMenu/images/Asser_PB_goFullScreen2_hover.png);" // вот да - другая картинка
            "   margin-bottom: -10px;" // а вот и само смещение
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

