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

private:
    Ui::MainWindow *ui;
    QRect m_previousGeometry; // обьявление переменной для сохранения геометрии (ГЫГЫ)


private slots:
    void GoTestButton_clicked(); // Метод для перехода к тестикам
    void GoStatButton_clicked(); // Метод Статистики
    void GoDecoderButton_clicked(); // Метод ДИЗАССЕМБЛИРОВАНИЯЯЯЯ
    void GoManualsButton_clicked(); // Метод покурить маны тупо расслабиться почилить почитать че Интел там написал ну тупо вызвать МЫСЛИ О СУИЦИДЕ (осуждаю)
    void AuthorButton_clicked(); // Метод для авторов (нет, я не устал писать // Метод )
    void ExitButton_clicked(); // Метод Выхода (после мануалов - только в окно)
    void SettingsButton_clicked(); // Метод настроек

    void goFullScreenButton_toggled(bool checked); //Метод для кнопки полного экрана



};
#endif // MAINWINDOW_H
