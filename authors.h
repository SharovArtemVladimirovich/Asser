#ifndef AUTHORS_H
#define AUTHORS_H

#include <QWidget>

namespace Ui {
class authors;
}

class authors : public QWidget
{
    Q_OBJECT

public:
    explicit authors(QWidget *parent = nullptr);
    ~authors();

private:
    Ui::authors *ui;

signals:
    void showMainReq();
    void showDonutReq();
};

#endif // AUTHORS_H
