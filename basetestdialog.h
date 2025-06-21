#ifndef BASETESTDIALOG_H
#define BASETESTDIALOG_H

#include "testtype.h"
#include "resultsdialog.h"

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QTime>
#include <QEvent>
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStyle>

// --- СТРУКТУРЫ ДАННЫХ ДЛЯ ВОПРОСОВ ---

// Структура для хранения правильного ответа в табличном вопросе
struct TableAnswer {
    int row;
    int col;
    QString correct;
};

// Структура для хранения ячейки таблицы (указатель на поле ввода и флаг, что ячейка нередактируема)
struct TableCell {
    QLineEdit* edit;
    bool isFixed;
};

// Главная структура, описывающая один вопрос в тесте
struct QuestionWidget {
    QString type;                               // Тип вопроса ("input", "table", etc.)
    QWidget* widget;                            // Виджет, который отображает весь вопрос
    QVector<QLineEdit*> edits;                  // Поля для ввода (для простых вопросов)
    QVector<QVector<TableCell>> tableEdits;     // Двумерный массив ячеек для табличных вопросов
    QVector<TableAnswer> tableAnswers;          // Правильные ответы для таблицы
    QString correct;                            // Правильный ответ (для простого вопроса)
    QVector<QString> corrects;                  // Правильные ответы (для вопроса с регистрами)
};


// --- ГЛАВНЫЙ КЛАСС ДИАЛОГА ТЕСТА ---

class BaseTestDialog : public QDialog {
    Q_OBJECT

public:
    // Конструктор: принимает тип теста, вариант и имя пользователя
    explicit BaseTestDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent = nullptr);
    virtual ~BaseTestDialog();

signals:
    // Сигнал, который испускается, когда тест завершен
    void testFinished();

protected slots:
    // --- Слоты (функции, которые реагируют на события) ---
    void updateTimer();             // Обновляет таймер каждую секунду
    void finishTest();              // Завершает тест (по кнопке)
    void goToNextPart();            // Переход к следующей части теста
    void goToPrevPart();            // Переход к предыдущей части теста
    void showCurrentPart();         // Отображает вопросы текущей части
    void updateNavButtons();        // Обновляет кнопки навигации (1, 2, 3...)
    void toggleMusic();             // Включить/выключить музыку
    void adjustVolume(int value);   // Регулировать громкость

protected:
    // --- Внутренние функции класса ---
    virtual void calculateScore();                                  // Подсчитывает очки (переопределяется в наследниках)
    virtual void loadQuestionsFromJson(const QString& filename);    // Загружает вопросы из JSON-файла

    void setupUI();                 // Настраивает пользовательский интерфейс
    void clearNavButtonSelection(); // Снимает выделение со всех кнопок навигации

    // --- Переменные-члены класса (хранят состояние) ---

    // Информация о тесте
    TestType currentTestType;
    QString currentVariant;
    QString currentUserName;
    QTime startTime;
    QVector<ResultEntry> results;

    // Вопросы
    QVector<QuestionWidget> part1Questions; // Вопросы для части 1
    QVector<QuestionWidget> part2Questions; // Вопросы для части 2
    QString part1Info;                      // Текст-описание для части 1
    QString part2Info;                      // Текст-описание для части 2
    int currentPart;                        // Текущая активная часть (0 или 1)
    int selectedNavButtonIndex = -1;        // Индекс выбранной кнопки навигации (-1, если ничего не выбрано)

    // Элементы интерфейса
    QWidget* questionsWidget;               // Виджет, где лежат все вопросы
    QVBoxLayout* questionsLayout;           // Менеджер компоновки для вопросов
    QScrollArea* scrollArea;                // Область прокрутки для вопросов

    // Таймер
    QLabel* timerLabel;
    QTimer* timer;
    int timeLeft;

    // Кнопки
    QPushButton* finishButton;
    QPushButton* nextPartButton;
    QPushButton* prevPartButton;

    // Навигация
    QGridLayout* navButtonsLayout;          // Менеджер компоновки для кнопок навигации
    QVector<QPushButton*> navButtons;       // Массив кнопок навигации

    // Музыкальный плеер
    QMediaPlayer* musicPlayer;
    QPushButton* musicButton;
    QSlider* volumeSlider;
    bool isMusicPlaying;
};

#endif // BASETESTDIALOG_H
