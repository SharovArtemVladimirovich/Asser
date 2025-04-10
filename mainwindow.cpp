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
    connect(ui -> ExitButton, &QPushButton::clicked, this, &MainWindow::ExitButton_clicked);
    connect(ui -> AuthorButton, &QPushButton::clicked, this, &MainWindow::AuthorButton_clicked);
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
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Выйти в окно");
    msgBox.setText("Ты точно уверен в этом?");
    QPushButton* yesButton = msgBox.addButton(QMessageBox::Yes);
    QPushButton* noButton = msgBox.addButton(QMessageBox::No);
    yesButton -> setText("Да, отчисляйте");
    noButton -> setText("Нет, простите");
    Authors *authorsWindow; //Ебучий костыль - надо исправить
    msgBox.exec();
    if (msgBox.clickedButton() == yesButton) {
        this -> close();
        authors.h -> close(); //Продолжение костыля - также исправить
    }
}


void MainWindow::on_SettingsButton_clicked() // Настройки
{

}

