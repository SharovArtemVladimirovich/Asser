#include "authors.h"
#include "ui_authors.h"
#include "mainwindow.h"
#include "style.h"

#include <QMovie>

authors::authors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authors)
{
    ui->setupUi(this);
    ui -> widget -> setStyleSheet (AuthorsST::StyleA);

    connect(ui -> AuthorsBackMMButton, &QPushButton::clicked, this, &authors::showMainReq);
    connect(ui -> DonutButton, &QPushButton::clicked, this, &authors::showDonutReq);

    QMovie *movie = new QMovie(":/gif/gif/Asser_AL.gif"); // Обьявлем под все добро переменную и суем в нее GIF из ресурсов
    ui -> AuthorLabel -> setMovie(movie); // Пихаем наш Виджет QMovie с муви в лейбл
    movie -> start(); // Не забываем запустить
}

authors::~authors()
{
    delete ui;
}
