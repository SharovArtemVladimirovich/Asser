#ifndef TESTTEMPLATEDIALOG_H
#define TESTTEMPLATEDIALOG_H
#include "testtype.h"
#include <QVBoxLayout>
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
struct TableAnswer {
    int row;
    int col;
    QString correct;
};

struct TableCell {
    QLineEdit* edit;
    bool isFixed;
};

struct QuestionWidget {
    QString type;
    QWidget* widget;
    QVector<QLineEdit*> edits;
    QVector<QVector<TableCell>> tableEdits;
    QVector<TableAnswer> tableAnswers;
    QString correct;
    QVector<QString> corrects;
};

class TestTemplateDialog : public QDialog {
    Q_OBJECT
public:
    explicit TestTemplateDialog(TestType testType, const QString& variant,
                               const QString& userName, QWidget *parent = nullptr);

signals:
    void testFinished();

private slots:
    void finishTest();
    void updateTimer();
    void goToNextPart();
    void goToPrevPart();

private:
    void loadQuestionsFromJson(const QString& filename);
    void setupUI();
    void showCurrentPart();
    void updateNavButtons();

    QVector<QuestionWidget> part1Questions;
    QVector<QuestionWidget> part2Questions;
    QString part1Info;
    QString part2Info;
    int currentPart = 0;

    QTimer* timer;
    QLabel* timerLabel;
    int timeLeft;
    QPushButton* finishButton;
    QPushButton* nextPartButton;
    QPushButton* prevPartButton;
    QWidget* questionsWidget;
    QVBoxLayout* questionsLayout;
    QVector<QPushButton*> navButtons;
    QGridLayout* navButtonsLayout;
    QScrollArea* scrollArea;

    TestType currentTestType;
    QString currentVariant;
    QString currentUserName;
    QTime startTime;
};

#endif // TESTTEMPLATEDIALOG_H
