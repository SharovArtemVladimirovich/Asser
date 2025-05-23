#include "testtemplatedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QScrollArea>
#include <QFrame>
#include <QHeaderView>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QScroller>
#include <QScrollBar>

TestTemplateDialog::TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent)
    : QDialog(parent), timeLeft(70*60), currentTestType(testType), currentVariant(variant), currentUserName(userName)
{
    setWindowTitle(QString("Тест - Вариант %1").arg(variant));
    resize(1100, 700);

    setupUI();

    QString testNumber;
    switch(testType) {
        case TestType::SystemSch: testNumber = "1"; break;
        case TestType::Mov: testNumber = "2"; break;
        case TestType::Arifmetic: testNumber = "3"; break;
        case TestType::Logic: testNumber = "4"; break;
        case TestType::Stack: testNumber = "5"; break;
        case TestType::Coding: testNumber = "6"; break;
        case TestType::Decoding: testNumber = "7"; break;
        default: testNumber = "1";
    }

    // Делаем так, чтобы variant был только числом
    QString variantNum = variant;
    variantNum.remove("Вариант");
    variantNum = variantNum.trimmed();

    QString jsonPath = QString(":/tests/test%1/variant%2.json")
                        .arg(testNumber)
                        .arg(variantNum);

    // Проверяем, существует ли файл
    QFile file(jsonPath);
    if (!file.exists()) {
        QMessageBox::critical(this, "Ошибка", "Файл с вопросами не найден: " + jsonPath);
        this->deleteLater();
        QTimer::singleShot(0, this, SLOT(close()));
        return;
    }

    loadQuestionsFromJson(jsonPath);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TestTemplateDialog::updateTimer);
    timer->start(1000);
}

void TestTemplateDialog::setupUI() {
    if (layout()) delete layout(); // Удаляем старый layout, если есть

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Центральная часть с вопросами
    questionsWidget = new QWidget;
    questionsLayout = new QVBoxLayout(questionsWidget);
    questionsLayout->setAlignment(Qt::AlignTop);
    questionsLayout->setSpacing(20);

    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(questionsWidget);
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    mainLayout->addWidget(scrollArea, 1);

    // Правая панель навигации
    QFrame* navFrame = new QFrame;
    navFrame->setFrameShape(QFrame::StyledPanel);
    navFrame->setFixedWidth(250);

    QVBoxLayout* navLayout = new QVBoxLayout(navFrame);
    navLayout->setSpacing(10);

    timerLabel = new QLabel("Оставшееся время: 01:10:00");
    timerLabel->setAlignment(Qt::AlignCenter);
    navLayout->addWidget(timerLabel);

    QLabel* navTitle = new QLabel("<b>Навигация по тесту</b>");
    navTitle->setAlignment(Qt::AlignCenter);
    navLayout->addWidget(navTitle);

    QWidget* buttonsWidget = new QWidget;
    navButtonsLayout = new QGridLayout(buttonsWidget);
    navButtonsLayout->setSpacing(5);
    navLayout->addWidget(buttonsWidget);

    finishButton = new QPushButton("Завершить попытку");
    navLayout->addWidget(finishButton);
    navLayout->addStretch();

    connect(finishButton, &QPushButton::clicked, this, &TestTemplateDialog::finishTest);

    mainLayout->addWidget(navFrame, 0);
}

void TestTemplateDialog::loadQuestionsFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Файл с вопросами не найден: " + filename);
        QTimer::singleShot(0, this, SLOT(close()));
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray arr = doc.array();

    int qIdx = 0;
    int navIdx = 0;
    for (const QJsonValue& v : arr) {
        QJsonObject obj = v.toObject();
        QString type = obj["type"].toString();

        QuestionWidget qw;
        qw.type = type;

        QFrame* frame = new QFrame;
        frame->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* vbox = new QVBoxLayout(frame);

        if (type == "info") {
            QLabel* infoLabel = new QLabel(obj["text"].toString());
            infoLabel->setWordWrap(true);
            vbox->addWidget(infoLabel);
        } else {
            QLabel* qLabel = new QLabel(obj["question"].toString());
            qLabel->setWordWrap(true);
            vbox->addWidget(qLabel);
        }

        if (type == "input") {
            QLineEdit* edit = new QLineEdit;
            vbox->addWidget(edit);
            qw.edits.append(edit);
            qw.correct = obj["correct_answer"].toString();
        }
        else if (type == "registers") {
            QJsonArray regs = obj["registers"].toArray();
            QHBoxLayout* regLayout = new QHBoxLayout;
            QVector<QLineEdit*> regEdits;
            QVector<QString> regCorrects;
            for (const QJsonValue& regVal : regs) {
                QJsonObject regObj = regVal.toObject();
                QString regName = regObj["name"].toString();
                QString correct = regObj["correct"].toString();

                QLabel* regLabel = new QLabel(regName + " =");
                QLineEdit* regEdit = new QLineEdit;
                regEdit->setFixedWidth(60);
                if (!correct.isEmpty()) {
                    regEdit->setText(correct);
                    regEdit->setReadOnly(true);
                }
                regLayout->addWidget(regLabel);
                regLayout->addWidget(regEdit);
                regEdits.append(regEdit);
                regCorrects.append(correct);
            }
            regLayout->addStretch();
            vbox->addLayout(regLayout);
            qw.edits = regEdits;
            qw.corrects = regCorrects; // ← сохраняем правильные ответы
        }
        else if (type == "table") {
            int rows = obj["rows"].toInt();
            QJsonArray columnsArr = obj["columns"].toArray();
            QStringList columns;
            for (const QJsonValue& col : columnsArr)
                columns << col.toString();

            QTableWidget* table = new QTableWidget(rows, columns.size());
            table->setHorizontalHeaderLabels(columns);
            table->verticalHeader()->setVisible(false);
            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            table->verticalHeader()->setDefaultSectionSize(30);
            table->setMinimumHeight(rows * 30 + 40);

            QVector<QVector<TableCell>> tableEdits(rows, QVector<TableCell>(columns.size()));
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < columns.size(); ++c) {
                    QLineEdit* edit = new QLineEdit;
                    edit->setReadOnly(false);
                    table->setCellWidget(r, c, edit);
                    tableEdits[r][c] = {edit, false};
                }
            }
            QJsonArray answers = obj["answers"].toArray();
            for (const QJsonValue& av : answers) {
                QJsonObject aobj = av.toObject();
                int row = aobj["row"].toInt();
                int col = aobj["col"].toInt();

                if (row >= 0 && row < rows && col >= 0 && col < columns.size()) {
                    if (aobj.contains("fixed") && aobj["fixed"].toBool()) {
                        QString value = aobj["value"].toString();
                        tableEdits[row][col].edit->setText(value);
                        tableEdits[row][col].edit->setReadOnly(true);
                        tableEdits[row][col].isFixed = true;
                    } else if (aobj.contains("correct")) {
                        QString correct = aobj["correct"].toString();
                        qw.tableAnswers.append({row, col, correct});
                    }
                }
            }
            qw.tableEdits = tableEdits;         // ← ОБЯЗАТЕЛЬНО!
            vbox->addWidget(table);             // ← ОБЯЗАТЕЛЬНО!
        }
        else if (type == "registers") {
            QJsonArray regs = obj["registers"].toArray();
            QHBoxLayout* regLayout = new QHBoxLayout;
            QVector<QLineEdit*> regEdits;
            for (const QJsonValue& regVal : regs) {
                QJsonObject regObj = regVal.toObject();
                QString regName = regObj["name"].toString();
                QString correct = regObj["correct"].toString();

                QLabel* regLabel = new QLabel(regName + " =");
                QLineEdit* regEdit = new QLineEdit;
                regEdit->setFixedWidth(60);
                if (!correct.isEmpty()) {
                    regEdit->setText(correct);
                    regEdit->setReadOnly(true);
                }
                regLayout->addWidget(regLabel);
                regLayout->addWidget(regEdit);
                regEdits.append(regEdit);
            }
            regLayout->addStretch();
            vbox->addLayout(regLayout);
            qw.edits = regEdits;
        }

        qw.widget = frame;
        questionWidgets.append(qw);
        questionsLayout->addWidget(frame);

        // Кнопка навигации (только для input/table, не для info)
        if (type == "input" || type == "table") {
            QPushButton* navBtn = new QPushButton(QString::number(navIdx + 1));
            navBtn->setCheckable(true);
            navBtn->setAutoExclusive(true);
            navBtn->setFixedSize(40, 40);
            navBtn->setStyleSheet("QPushButton { margin: 2px; }");
            connect(navBtn, &QPushButton::clicked, this, [this, navIdx]() { scrollToQuestion(navIdx); });
            navButtons.append(navBtn);

            int row = navIdx / 4;
            int col = navIdx % 4;
            navButtonsLayout->addWidget(navBtn, row, col);
            navIdx++;
        }

        ++qIdx;
    }
    questionsLayout->addStretch();
}

void TestTemplateDialog::scrollToQuestion(int idx) {
    if (idx < 0 || idx >= questionWidgets.size()) return;
    QWidget* w = questionWidgets[idx].widget;
    w->setFocus();
    if (scrollArea) {
        // Прокручиваем так, чтобы вопрос был в самом верху
        QPoint relPos = w->mapTo(questionsWidget, QPoint(0, 0));
        scrollArea->verticalScrollBar()->setValue(relPos.y());
    }
}

void TestTemplateDialog::updateTimer() {
    --timeLeft;
    int hours = timeLeft / 3600;
    int min = (timeLeft % 3600) / 60;
    int sec = timeLeft % 60;
    timerLabel->setText(QString("Оставшееся время: %1:%2:%3")
                        .arg(hours, 2, 10, QChar('0'))
                        .arg(min, 2, 10, QChar('0'))
                        .arg(sec, 2, 10, QChar('0')));
    if (timeLeft <= 0) {
        timer->stop();
        QMessageBox::information(this, "Время вышло", "Время теста истекло!");
        finishTest();
    }
}

void TestTemplateDialog::finishTest() {
    timer->stop();
    int correct = 0, total = 0;
    int qNum = 1;
    QStringList wrong;

    for (const auto& qw : questionWidgets) {
        // Проверка input-вопросов (одно поле для ввода)
        if (qw.type == "input") {
            ++total; // Всегда увеличиваем total, даже если поле пустое
            QString user = qw.edits[0]->text().trimmed();
            QString correctAns = qw.correct;
            if (user == correctAns)
                ++correct; // Ответ правильный
            else
                wrong << QString::number(qNum); // Ответ неправильный или пустой, добавляем в ошибки
        }
        // Проверка registers-вопросов (несколько полей для ввода)
        else if (qw.type == "registers") {
            for (int i = 0; i < qw.edits.size(); ++i) {
                if (qw.corrects[i].isEmpty()) continue; // Не проверяем те, где нет правильного ответа
                ++total; // Всегда увеличиваем total, даже если поле пустое
                QString user = qw.edits[i]->text().trimmed();
                QString correctAns = qw.corrects[i];
                if (user == correctAns)
                    ++correct; // Ответ правильный
                else
                    wrong << QString("%1 (%2)").arg(qNum).arg(i+1); // Ответ неправильный или пустой, добавляем в ошибки
            }
        }
        // Проверка table-вопросов (таблица с несколькими полями для ввода)
        else if (qw.type == "table") {
            for (const auto& ta : qw.tableAnswers) {
                // Пропускаем фиксированные (readonly) ячейки
                if (qw.tableEdits[ta.row][ta.col].isFixed) continue;
                ++total; // Всегда увеличиваем total, даже если поле пустое
                QString user = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                QString correctAns = ta.correct;
                if (user == correctAns)
                    ++correct; // Ответ правильный
                else
                    wrong << QString("Таблица %1 [%2,%3]").arg(qNum).arg(ta.row+1).arg(ta.col+1); // Ответ неправильный или пустой, добавляем в ошибки
            }
        }
        ++qNum;
    }

    double score = (total > 0) ? (8.0 * correct / total) : 0.0;
    QString scoreStr = QString::number(score, 'f', 2);

    QString result = QString("%1\nВаш результат: %2 из 8.00 баллов")
                    .arg(currentUserName)
                    .arg(scoreStr);
    if (!wrong.isEmpty())
        result += "\nОшибки в вопросах: " + wrong.join(", ");

    QMessageBox::information(this, "Результат", result);
    emit testFinished();
    accept();
}
