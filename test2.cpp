#include "test2.h"
#include <QTime>
#include "resultsdialog.h"

Test2::Test2(const QString& variant, const QString& userName, QWidget* parent)
    : BaseTestDialog(TestType::Mov, variant, userName, parent)
{
}

void Test2::calculateScore()
{
    double totalScore = 0.0;
    double maxScore = 8.0;

    results.clear();

    int totalQuestionsCounted = 40;
    double perQuestionScore = maxScore / totalQuestionsCounted;

    auto scoreQuestions = [&](const QVector<QuestionWidget>& questions, int partNum) {
        for (int qIndex = 0; qIndex < questions.size(); ++qIndex) {
            const auto& qw = questions[qIndex];
            if (!qw.widget) continue;

            bool allCorrect = true;
            QString questionText = qw.widget->findChild<QLabel*>()->text();
            QString userAnswer = "";

            if (qw.type != "table") {
                if (!qw.edits.isEmpty()) {
                    QStringList userEdits;
                    for (int i = 0; i < qw.edits.size(); ++i) {
                        QString userText = qw.edits[i]->text().trimmed();
                        if (!userText.isEmpty()) userEdits.append(userText);
                        if (i >= qw.corrects.size()) {
                            allCorrect = false;
                            break;
                        } else {
                            QString correctText = qw.corrects[i].trimmed();
                            if (userText.toUpper() != correctText.toUpper()) {
                                allCorrect = false;
                            }
                        }
                    }
                    userAnswer = userEdits.join(", ");
                } else {
                    allCorrect = true;
                    userAnswer = "";
                }
            } else {
                QStringList tableUserAnswers;
                for (const auto& ta : qw.tableAnswers) {
                    if (ta.row < qw.tableEdits.size() && ta.col < qw.tableEdits[ta.row].size()) {
                        if (!qw.tableEdits[ta.row][ta.col].isFixed) {
                            QString cellText = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                            if (!cellText.isEmpty()) tableUserAnswers.append(QString("[%1,%2]:%3").arg(ta.row).arg(ta.col).arg(cellText));
                            if (cellText.toUpper() != ta.correct.toUpper()) {
                                allCorrect = false;
                            }
                        }
                    } else {
                        allCorrect = false;
                    }
                }
                userAnswer = tableUserAnswers.join(", ");
            }

            if (allCorrect) {
                totalScore += perQuestionScore;
                results.append(ResultEntry{questionText, userAnswer, perQuestionScore, perQuestionScore, partNum});
            } else {
                results.append(ResultEntry{questionText, userAnswer, 0.0, perQuestionScore, partNum});
            }
        }
    };

    scoreQuestions(part1Questions, 1);
    scoreQuestions(part2Questions, 2);

    QTime endTime = QTime::currentTime();
    int secs = startTime.secsTo(endTime);
    QString timeSpent = QString("%1:%2:%3")
        .arg(secs/3600, 2, 10, QChar('0'))
        .arg((secs%3600)/60, 2, 10, QChar('0'))
        .arg(secs%60, 2, 10, QChar('0'));

    ResultsDialog dlg(results, totalScore, timeSpent, currentUserName, this);
    dlg.exec();
    emit testFinished();
    accept();
}
