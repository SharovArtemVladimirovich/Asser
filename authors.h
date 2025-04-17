#ifndef AUTHORS_H
#define AUTHORS_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Authors;
}

class Authors : public QWidget
{
    Q_OBJECT

public:
    explicit Authors(QWidget *parent = nullptr);

    ~Authors();

private slots:

    void AuthorsBackMMButton_clicked();
    void DonutButton_clicked();

private:
    Ui::Authors *ui;

};

#endif // AUTHORS_H
