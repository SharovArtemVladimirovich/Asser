#include "testtemplatedialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>

TestTemplateDialog::TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent)
    : QDialog(parent), currentTestType(testType), currentVariant(variant), currentUserName(userName) {

    QWidget *centralContainer = new QWidget(this);
    centralContainer->setFixedWidth(600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    loadQuestions();

}

void TestTemplateDialog::loadQuestions() {
    // Формирование имени файла
    QString filename;
    switch (currentTestType) {
        case TestType::SystemSch:
            filename = "system_sch";
            break;
        case TestType::Mov:
            filename = "mov";
            break;
        case TestType::Arifmetic:
            filename = "arifmetic";
            break;
        case TestType::Logic:
            filename = "logic";
            break;
        case TestType::Stack:
            filename = "stack";
            break;
        case TestType::Coding:
            filename = "coding";
            break;
        case TestType::Decoding:
            filename = "decoding";
            break;
        default:
            filename = "unknown";
    }
    filename += "_variant_" + currentVariant.split(" ").last() + ".json";

    // Открытие файла
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Файл с вопросами не найден: " + filename);
        return;
    }

    // Парсинг JSON
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::critical(this, "Ошибка", "Ошибка формата JSON: " + parseError.errorString());
        return;
    }

    if (!doc.isArray()) {
        QMessageBox::critical(this, "Ошибка", "Файл должен содержать массив вопросов");
        return;
    }

    // Очистка предыдущих виджетов
    QLayoutItem *child;
    while ((child = layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Загрузка вопросов
    QJsonArray questions = doc.array();
    for (const QJsonValue &questionValue : questions) {
        QJsonObject questionObj = questionValue.toObject();
        QString questionText = questionObj["question"].toString();
        QString type = questionObj["type"].toString();

        // Виджет вопроса
        QLabel *questionLabel = new QLabel(questionText, this);
        layout()->addWidget(questionLabel);

        // Виджет ответа
        if (type == "input") {
            QLineEdit *answerInput = new QLineEdit(this);
            layout()->addWidget(answerInput);
            inputAnswers.append({answerInput, questionObj["correct_answer"].toString()});

        } else if (type == "conversion_table") {
            // Создание таблицы
            QLabel *titleLabel = new QLabel(questionObj["title"].toString(), this);
            layout()->addWidget(titleLabel);

            QTableWidget *table = new QTableWidget(this);
            QStringList columns = questionObj["columns"].toVariant().toStringList();
            QJsonArray rows = questionObj["rows"].toArray();

            table->setColumnCount(columns.size());
            table->setRowCount(rows.size());
            table->setHorizontalHeaderLabels(columns);

            for (int rowIdx = 0; rowIdx < rows.size(); ++rowIdx) {
                QJsonObject rowObj = rows[rowIdx].toObject();
                for (int colIdx = 0; colIdx < columns.size(); ++colIdx) {
                    QString columnName = columns[colIdx];
                    QJsonObject cell = rowObj[columnName].toObject();

                    QLineEdit *input = new QLineEdit(cell["value"].toString());
                    input->setProperty("correct_answer", cell["correct"].toString());
                    table->setCellWidget(rowIdx, colIdx, input);
                }
            }

            layout()->addWidget(table);
        }
    }

    // Кнопка завершения теста
    QPushButton *finishButton = new QPushButton("Завершить тест", this);
    connect(finishButton, &QPushButton::clicked, this, &TestTemplateDialog::finishTest);
    layout()->addWidget(finishButton);
}

void TestTemplateDialog::finishTest() {
    int correct = 0;
    int total = inputAnswers.size();

    QList<QTableWidget*> tables = findChildren<QTableWidget*>();
        for (QTableWidget *table : tables) {
            for (int row = 0; row < table->rowCount(); ++row) {
                for (int col = 0; col < table->columnCount(); ++col) {
                    QLineEdit *input = qobject_cast<QLineEdit*>(table->cellWidget(row, col));
                    if (input) {
                        total++;
                        QString correctAnswer = input->property("correct_answer").toString();
                        if (input->text().trimmed() == correctAnswer) {
                            correct++;
                        }
                    }
                }
            }
        }

    // Проверка текстовых ответов
    for (const auto &pair : inputAnswers) {
        if (pair.first->text().trimmed() == pair.second) {
            correct++;
    }

    emit testFinished(); // Испускаем сигнал
        accept();
}

    // Вывод результата
    QMessageBox::information(this, "Результат",
        QString("%1, ваш результат: %2 из %3")
            .arg(currentUserName)
            .arg(correct)
            .arg(total));
}
