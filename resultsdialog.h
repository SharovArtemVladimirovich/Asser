#pragma once
#include <QDialog>
#include <QVector>
#include <QString>

struct ResultEntry {
    QString question;
    QString userAnswer;
    double score;
    double maxScore;
    int part; // 1 или 2
};

class ResultsDialog : public QDialog {
    Q_OBJECT
public:
    ResultsDialog(const QVector<ResultEntry>& results, double totalScore, const QString& timeSpent, QWidget* parent = nullptr);
};
