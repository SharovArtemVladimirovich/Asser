#ifndef DONUT_H
#define DONUT_H

#include <QWidget>

namespace Ui {
class Donut;
}

class Donut : public QWidget
{
    Q_OBJECT

public:
    explicit Donut(QWidget *parent = nullptr);
    ~Donut();

private:
    Ui::Donut *ui;

signals:
    void showAuthorsReq();
};

#endif // DONUT_H
