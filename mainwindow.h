#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authors.h" // Добавили класс Авторов как доп окно

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void GoTestButton_clicked();
    void GoStatButton_clicked();
    void GoDecoderButton_clicked();
    void GoManualsButton_clicked();
    void AuthorButton_clicked();
    void ExitButton_clicked();

    void on_SettingsButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
