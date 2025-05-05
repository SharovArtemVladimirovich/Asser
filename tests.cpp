#include "tests.h"
#include "ui_tests.h"
#include "mainwindow.h"
#include "style.h"

#include <QFile>
tests::tests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tests)
{
    ui -> setupUi(this);
    ui -> widgetTests -> setStyleSheet (TestsST::StyleT);

    connect(ui -> MainBackButton, &QPushButton::clicked, this, &tests::showMainReq);
}

tests::~tests()
{
    delete ui;
}
