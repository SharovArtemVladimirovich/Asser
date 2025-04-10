#ifndef AUTHORS_H
#define AUTHORS_H

#include <QWidget>

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

private:
    Ui::Authors *ui;

};

#endif // AUTHORS_H
