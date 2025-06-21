#include "test1.h"
#include <QTime>
#include "resultsdialog.h"

Test1::Test1(const QString& variant, const QString& userName, QWidget* parent)
// Эта строка вызывает конструктор родительского класса (BaseTestDialog)
    // и передает ему всю нужную информацию, включая тип теста (SystemSch).
    : BaseTestDialog(TestType::SystemSch, variant, userName, parent)
{
    // Сам конструктор пустой, потому что вся настройка интерфейса
        // происходит в родительском классе BaseTestDialog.
}
// =================================================================
// CALCULATE SCORE - ГЛАВНАЯ ФУНКЦИЯ ПОДСЧЁТА БАЛЛОВ
// Эта функция переопределяет "пустую" функцию из BaseTestDialog
// и содержит уникальную логику для этого конкретного теста.
// =================================================================
void Test1::calculateScore()
{
    double totalScore = 0.0;//итоговый балл
    double maxScore = 8.0;//макс балл

    results.clear();//Очищаем на всякий случай

    int totalIndividualFillableItems = 0; //счетчик всех полей для ответов

    auto countFillableItems = [&](const QVector<QuestionWidget>& questions) {
        for (const auto& qw : questions) {
            if (!qw.widget) continue;
            if (qw.type == "input") {
                totalIndividualFillableItems += 1;
            } else if (qw.type == "registers") {
                totalIndividualFillableItems += qw.edits.size();
            } else if (qw.type == "table") {
                for (const auto& ta : qw.tableAnswers) {
                    // Считаем только те ячейки, которые не являются "фиксированными
                    if (ta.row < qw.tableEdits.size() && ta.col < qw.tableEdits[ta.row].size() && !qw.tableEdits[ta.row][ta.col].isFixed) {
                        totalIndividualFillableItems++;
                    }
                }
            }
        }
    };
// Запускаем подсчёт для первой части
    countFillableItems(part1Questions);
 // countFillableItems(part2Questions); // Если бы была вторая часть, мы бы посчитали и её
// Теперь вычисляем "стоимость" одного правильного ответа
    double perIndividualItemScore = (totalIndividualFillableItems > 0) ? maxScore / totalIndividualFillableItems : 0.0;
//ПРОВЕРКА ОТВЕТОВ И НАЧИСЛЕНИЕ БАЛЛОВ ---
// Лямбда-функция, которая проходит по всем вопросам, сравнивает ответы и начисляет баллы.
    auto scoreAndLogItems = [&](const QVector<QuestionWidget>& questions, int partNum) {
        for (int qIndex = 0; qIndex < questions.size(); ++qIndex) {
            const auto& qw = questions[qIndex];
            if (!qw.widget) continue;
            QString baseQuestionText = qw.widget->findChild<QLabel*>()->text();
            double currentQuestionScore = 0.0;//балл за текущий вопрос
            QString currentQuestionUserAnswer = "";//ответ пользователя
            double currentQuestionMaxScore = 0.0;//начисляем балл

            if (qw.type == "input") {
                currentQuestionMaxScore = perIndividualItemScore;
                QString userAnswerText = qw.edits[0]->text().trimmed();
                currentQuestionUserAnswer = userAnswerText;
                if (userAnswerText.toUpper() == qw.correct.toUpper()) {
                    currentQuestionScore = perIndividualItemScore;
                }
            } else if (qw.type == "registers") {
                int correctRegs = 0;
                int totalRegsInQuestion = 0;
                QStringList userRegAnswers;

                for (int i = 0; i < qw.edits.size(); ++i) {
                    if (i >= qw.corrects.size() || qw.corrects[i].isEmpty()) continue;
                    totalRegsInQuestion++;
                    QString userRegText = qw.edits[i]->text().trimmed();
                    if (!userRegText.isEmpty()) userRegAnswers.append(userRegText);
                    QString correctAns = qw.corrects[i].trimmed();
                    if (userRegText.toUpper() == correctAns.toUpper()) {
                        correctRegs++;
                    }
                }
                currentQuestionScore = perIndividualItemScore * correctRegs;
                currentQuestionMaxScore = perIndividualItemScore * totalRegsInQuestion;
                currentQuestionUserAnswer = userRegAnswers.join(", ");
            } else if (qw.type == "table") {
                QStringList userTableAnswers;
                int correctCells = 0;
                int totalFillableCellsInTable = 0;

                for (const auto& ta : qw.tableAnswers) {
                    if (ta.row < qw.tableEdits.size() && ta.col < qw.tableEdits[ta.row].size()) {
                        if (!qw.tableEdits[ta.row][ta.col].isFixed) {
                            totalFillableCellsInTable++;
                            QString cellText = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                            if (!cellText.isEmpty()) userTableAnswers.append(QString("[%1,%2]:%3").arg(ta.row).arg(ta.col).arg(cellText));
                            if (cellText.toUpper() == ta.correct.toUpper()) {
                                correctCells++;
                            }
                        }
                    }
                }
                currentQuestionScore = perIndividualItemScore * correctCells;
                currentQuestionMaxScore = perIndividualItemScore * totalFillableCellsInTable;
                currentQuestionUserAnswer = userTableAnswers.join(", ");
            }
   // Добавляем начисленный балл к общему счету
            totalScore += currentQuestionScore;
    // Записываем подробный результат по этому вопросу в массив для итогового отчета
            results.append(ResultEntry{baseQuestionText, currentQuestionUserAnswer, currentQuestionScore, currentQuestionMaxScore, partNum});
        }
    };

    scoreAndLogItems(part1Questions, 1);
//---ОТОБРАЖЕНИЕ РЕЗУЛЬТАТОВ ---

// Вычисляем общее время, потраченное на тест
    QTime endTime = QTime::currentTime();
    int secs = startTime.secsTo(endTime);
    QString timeSpent = QString("%1:%2:%3")
        .arg(secs/3600, 2, 10, QChar('0'))
        .arg((secs%3600)/60, 2, 10, QChar('0'))
        .arg(secs%60, 2, 10, QChar('0'));
// Создаем и показываем диалоговое окно с результатами
    ResultsDialog dlg(results, totalScore, timeSpent, currentUserName, this);
    dlg.exec();
// Сообщаем программе, что тест завершен
    emit testFinished();
    accept();//закрываем окно теста
}
