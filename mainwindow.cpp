#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "authors.h"
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Asser");
    connect(ui -> ExitButton, &QPushButton::clicked, this, &MainWindow::ExitButton_clicked); //СОЕДИНЕНИЕ кнопки ВЫХОД
    connect(ui -> AuthorButton, &QPushButton::clicked, this, &MainWindow::AuthorButton_clicked); //Соединение кнопки АВТОРЫ
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
    Authors *authorsWindow; //Ебучий костыль - надо исправить (Рожденный чтобы быть убитым лол)
    msgBox.exec(); //Че то типо запуска нашего Массажного Коробка
    if (msgBox.clickedButton() == yesButton) { //проверка на то, нажата ли кнопка ДА в массажном боксе (обращение к классу msgBox свойству clickedButton() )
        this -> close(); // Убиваем MEIN меню
        authorsWindow -> close(); //Убиваем окно с авторами. Продолжение костыля - также исправить.
    }
}


void MainWindow::on_SettingsButton_clicked() // Настройки
{

}

