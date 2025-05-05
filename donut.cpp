#include "donut.h"
#include "ui_donut.h"
#include "style.h"

Donut::Donut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Donut)
{
    ui->setupUi(this);
    ui -> widget -> setStyleSheet (DonutST::StyleD);

    connect(ui -> goBackToAuthorsButton, &QPushButton::clicked, this, &Donut::showAuthorsReq);
}

Donut::~Donut()
{
    delete ui;
}
