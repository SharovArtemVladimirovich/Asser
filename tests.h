#ifndef TESTS_H
#define TESTS_H

#include <QWidget>

namespace Ui {
class tests;
}

class tests : public QWidget
{
    Q_OBJECT

public:
    explicit tests(QWidget *parent = nullptr);
    ~tests();

private:
    Ui::tests *ui;

signals:
    void showMainReq();

};

#endif // TESTS_H
