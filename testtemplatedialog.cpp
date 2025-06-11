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
#include "resultsdialog.h"
#include <QTime>

TestTemplateDialog::TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent)
    : QDialog(parent), timeLeft(70*60), currentTestType(testType), currentVariant(variant), currentUserName(userName)
{
    setWindowTitle(QString("Тест - Вариант %1").arg(variant));
    resize(1100, 700);

    startTime = QTime::currentTime();

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
    // Создаем кнопки для перехода между частями
    nextPartButton = new QPushButton("Следующая страница", this);
    prevPartButton = new QPushButton("Предыдущая страница", this);

    connect(nextPartButton, &QPushButton::clicked, this, &TestTemplateDialog::goToNextPart);
    connect(prevPartButton, &QPushButton::clicked, this, &TestTemplateDialog::goToPrevPart);

    nextPartButton->setVisible(false);
    prevPartButton->setVisible(false);
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

    part1Questions.clear();
    part2Questions.clear();
    part1Info.clear();
    part2Info.clear();
    int part = 0;
    bool hasPart2 = false;
    for (const QJsonValue& v : arr) {
        QJsonObject obj = v.toObject();
        QString type = obj["type"].toString();
        if (type == "info") {
            QString text = obj["text"].toString();
            if (text.contains("Часть 2")) {
                part = 1;
                hasPart2 = true;
                part2Info = text;
            } else {
                part1Info = text;
            }
            continue;
        }
        QuestionWidget qw;
        qw.type = type;
        QFrame* frame = new QFrame;
        frame->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* vbox = new QVBoxLayout(frame);
        QLabel* qLabel = new QLabel(obj["question"].toString());
        qLabel->setWordWrap(true);
        vbox->addWidget(qLabel);
        if (type == "input") {
            QLineEdit* edit = new QLineEdit;
            vbox->addWidget(edit);
            qw.edits.append(edit);
            qw.correct = obj["correct_answer"].toString();
        } else if (type == "registers") {
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
                regLayout->addWidget(regLabel);
                regLayout->addWidget(regEdit);
                regEdits.append(regEdit);
                regCorrects.append(correct);
            }
            regLayout->addStretch();
            vbox->addLayout(regLayout);
            qw.edits = regEdits;
            qw.corrects = regCorrects;
        } else if (type == "table") {
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
            qw.tableEdits = tableEdits;
            vbox->addWidget(table);
        }
        qw.widget = frame;
                if (part == 0) part1Questions.append(qw);
                else part2Questions.append(qw);
            }
            currentPart = 0;
            showCurrentPart();
}
void TestTemplateDialog::showCurrentPart() {
    // Очищаем layout
    QLayoutItem* child;
    while ((child = questionsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->setParent(nullptr); // detach, не delete!
        delete child;
    }

    // Добавляем info, только если он есть
    QString infoText = (currentPart == 0 ? part1Info : part2Info);
    if (!infoText.isEmpty()) {
        QLabel* info = new QLabel(infoText);
        info->setWordWrap(true);
        info->setStyleSheet("font-weight: bold; background: #eef; padding: 8px; border-radius: 6px;");
        questionsLayout->addWidget(info);
    }

    // Добавляем вопросы
    const QVector<QuestionWidget>& questions = (currentPart == 0 ? part1Questions : part2Questions);
    for (const auto& qw : questions) {
        questionsLayout->addWidget(qw.widget);
    }

    // Кнопки перехода между частями только если есть обе части
    if (!part2Questions.isEmpty()) {
        if (currentPart == 0) {
            if (questionsLayout->indexOf(nextPartButton) == -1)
                questionsLayout->addWidget(nextPartButton);
            nextPartButton->setVisible(true);
            prevPartButton->setVisible(false);
        } else {
            if (questionsLayout->indexOf(prevPartButton) == -1)
                questionsLayout->addWidget(prevPartButton);
            prevPartButton->setVisible(true);
            nextPartButton->setVisible(false);
        }
    } else {
        nextPartButton->setVisible(false);
        prevPartButton->setVisible(false);
    }

    questionsLayout->addStretch();
    updateNavButtons();

    // Скроллим в начало
    QTimer::singleShot(0, [this]() {
        if (scrollArea && scrollArea->verticalScrollBar()) {
            scrollArea->verticalScrollBar()->setValue(0);
        }
    });
}

void TestTemplateDialog::goToNextPart() {
    if (currentPart == 0 && !part2Questions.isEmpty()) {
        currentPart = 1;
        showCurrentPart();
    }
}
void TestTemplateDialog::goToPrevPart() {
    if (currentPart == 1) {
        currentPart = 0;
        showCurrentPart();
    }
}
void TestTemplateDialog::updateNavButtons() {
    // Очищаем старые кнопки
    QLayoutItem* child;
    while ((child = navButtonsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }
    navButtons.clear();
    const QVector<QuestionWidget>& questions = (currentPart == 0 ? part1Questions : part2Questions);
    for (int i = 0; i < questions.size(); ++i) {
        QPushButton* navBtn = new QPushButton(QString::number(i + 1));
        navBtn->setCheckable(true);
        navBtn->setAutoExclusive(true);
        navBtn->setFixedSize(40, 40);
        navBtn->setStyleSheet("QPushButton { margin: 2px; }");
        connect(navBtn, &QPushButton::clicked, this, [this, i]() {
            QWidget* w = (currentPart == 0 ? part1Questions[i].widget : part2Questions[i].widget);
            w->setFocus();
            if (scrollArea) {
                QPoint relPos = w->mapTo(questionsWidget, QPoint(0, 0));
                scrollArea->verticalScrollBar()->setValue(relPos.y());
            }
        });
        navButtons.append(navBtn);
        int row = i / 4;
        int col = i % 4;
        navButtonsLayout->addWidget(navBtn, row, col);
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
    // Показываем диалог подтверждения
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Подтверждение",
        "Вы точно уверены, что хотите завершить тест?",
        QMessageBox::Yes | QMessageBox::No
    );
    if (reply != QMessageBox::Yes) {
        return; // Пользователь отменил завершение
    }
    timer->stop();
    QVector<ResultEntry> results;
    double totalScore = 0.0;
    double maxScore = 8.0;
    int totalQuestions = part1Questions.size() + part2Questions.size();
    double perQuestion = maxScore / (totalQuestions > 0 ? totalQuestions : 1);
    int idx = 0;
    // Часть 1
    for (const auto& qw : part1Questions) {
        QString userAns;
        double score = 0.0;
        if (qw.type == "input") {
            userAns = qw.edits[0]->text().trimmed();
            if (userAns == qw.correct)
                score = perQuestion;
        } else if (qw.type == "registers") {
            QStringList userList;
            int localCorrect = 0, localTotal = 0;
            for (int i = 0; i < qw.edits.size(); ++i) {
                if (qw.corrects[i].isEmpty()) continue;
                ++localTotal;
                QString user = qw.edits[i]->text().trimmed();
                if (!user.isEmpty()) userList << user;
                if (user == qw.corrects[i]) ++localCorrect;
            }
            userAns = userList.join(", ");
            if (localTotal > 0) score = perQuestion * localCorrect / localTotal;
        } else if (qw.type == "table") {
            QStringList userList;
            int localCorrect = 0, localTotal = 0;
            for (const auto& ta : qw.tableAnswers) {
                if (qw.tableEdits[ta.row][ta.col].isFixed) continue;
                ++localTotal;
                QString user = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                if (!user.isEmpty()) userList << user;
                if (user == ta.correct) ++localCorrect;
            }
            userAns = userList.join(", ");
            if (localTotal > 0) score = perQuestion * localCorrect / localTotal;
        }
        QLabel* label = qw.widget->findChild<QLabel*>();
        QString questionText = label ? label->text() : QString("Вопрос %1").arg(idx+1);
        results.append({questionText, userAns, score, perQuestion, 1});
        totalScore += score;
        ++idx;
    }
    // Часть 2
    for (const auto& qw : part2Questions) {
        QString userAns;
        double score = 0.0;
        if (qw.type == "input") {
            userAns = qw.edits[0]->text().trimmed();
            if (userAns == qw.correct)
                score = perQuestion;
        } else if (qw.type == "registers") {
            QStringList userList;
            int localCorrect = 0, localTotal = 0;
            for (int i = 0; i < qw.edits.size(); ++i) {
                if (qw.corrects[i].isEmpty()) continue;
                ++localTotal;
                QString user = qw.edits[i]->text().trimmed();
                if (!user.isEmpty()) userList << user;
                if (user == qw.corrects[i]) ++localCorrect;
            }
            userAns = userList.join(", ");
            if (localTotal > 0) score = perQuestion * localCorrect / localTotal;
        } else if (qw.type == "table") {
            QStringList userList;
            int localCorrect = 0, localTotal = 0;
            for (const auto& ta : qw.tableAnswers) {
                if (qw.tableEdits[ta.row][ta.col].isFixed) continue;
                ++localTotal;
                QString user = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                if (!user.isEmpty()) userList << user;
                if (user == ta.correct) ++localCorrect;
            }
            userAns = userList.join(", ");
            if (localTotal > 0) score = perQuestion * localCorrect / localTotal;
        }
        QLabel* label = qw.widget->findChild<QLabel*>();
        QString questionText = label ? label->text() : QString("Вопрос %1").arg(idx+1);
        results.append({questionText, userAns, score, perQuestion, 2});
        totalScore += score;
        ++idx;
    }
    QTime endTime = QTime::currentTime();
    int secs = startTime.secsTo(endTime);
    QString timeSpent = QString("%1:%2").arg(secs/60,2,10,QChar('0')).arg(secs%60,2,10,QChar('0'));
    ResultsDialog dlg(results, totalScore, timeSpent, this);
    dlg.exec();
    emit testFinished();
    accept();
}
