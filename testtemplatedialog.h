#ifndef TESTTEMPLATEDIALOG_H
#define TESTTEMPLATEDIALOG_H

#include "testtype.h"
#include "resultsdialog.h"

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
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStyle>

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
    explicit TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent = nullptr);
    ~TestTemplateDialog();

signals:
    void testFinished();

private slots:
    void updateTimer();
    void finishTest();
    void goToNextPart();
    void goToPrevPart();
    void createNavigationButtons();
    void calculateScore();
    void showCurrentPart();
    void updateNavButtons();
    void toggleMusic();
    void adjustVolume(int value);

private:
    void setupUI();
    void loadQuestionsFromJson(const QString& filename);

    QVector<QuestionWidget> part1Questions;
    QVector<QuestionWidget> part2Questions;
    QString part1Info;
    QString part2Info;
    int currentPart;
    QWidget* questionsWidget;
    QVBoxLayout* questionsLayout;
    QScrollArea* scrollArea;

    QLabel* timerLabel;
    QTimer* timer;
    int timeLeft;
    QPushButton* finishButton;
    QPushButton* nextPartButton;
    QPushButton* prevPartButton;
    QGridLayout* navButtonsLayout;
    QVector<QPushButton*> navButtons;

    TestType currentTestType;
    QString currentVariant;
    QString currentUserName;
    QTime startTime;
    QVector<ResultEntry> results;

    QMediaPlayer* musicPlayer;
    QPushButton* musicButton;
    QSlider* volumeSlider;
    bool isMusicPlaying;
};

#endif // TESTTEMPLATEDIALOG_H
