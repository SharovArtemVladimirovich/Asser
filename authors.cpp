#include "authors.h"
#include "ui_authors.h"

Authors::Authors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authors)
{
    ui->setupUi(this);
    setWindowTitle("Asser.Authors"); //Ставим крутой заголовок окна
    connect(ui -> AuthorsBackMMButton, &QPushButton::clicked, this, &Authors::AuthorsBackMMButton_clicked); //конектим кнопку для AuthorsBackMMButton
    connect(ui -> DonutButton, &QPushButton::clicked, this, &Authors::DonutButton_clicked); //конектим кнопку для ДОНАТОВ
}

Authors::~Authors()
{
    delete ui;
}

void Authors::AuthorsBackMMButton_clicked() //просто возвращаемся в главное меню (Сложный код)
{

    this -> close();

}


void Authors::DonutButton_clicked() //кнопаха для Попаха(доната)
{

}

