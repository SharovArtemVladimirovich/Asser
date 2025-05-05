#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>


namespace Ui {
class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen();
private slots:
    void quitButton_clicked();

private:
    Ui::MainScreen *ui;

signals:
    void showTestsReq();
    void showAuthorsReq();
    void showManualsReq();
};

#endif // MAINSCREEN_H
