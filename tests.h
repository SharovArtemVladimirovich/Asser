#ifndef TESTS_H
#define TESTS_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include "testtype.h"

namespace Ui {
class tests;
}

class tests : public QWidget
{
    Q_OBJECT

public:
    explicit tests(QWidget *parent = nullptr);
    ~tests();

private slots:

private:
    void setupTestButtons();
    Ui::tests *ui;
    QVector<QPushButton*> testButtons;
    QVector<TestType> testTypes; // Типы для 7 кнопок

signals:
    void showMainReq();
    void testRequested(TestType type, const QString& userName, const QString& variant);

};

#endif // TESTS_H
