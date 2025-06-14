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
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QStyle>

// Конструктор диалога теста
TestTemplateDialog::TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent)
    : QDialog(parent), timeLeft(70*60), currentTestType(testType), currentVariant(variant),
      currentUserName(userName), currentPart(0), isMusicPlaying(false)
{
    setWindowTitle(QString("Тест - Вариант %1").arg(variant));
    resize(1100, 700);

    startTime = QTime::currentTime();

    // Настройка интерфейса
    setupUI();

    // Определяем номер теста для загрузки правильного JSON файла
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

    // Формируем путь к JSON файлу с вопросами
    QString variantNum = variant;
    variantNum.remove("Вариант");
    variantNum = variantNum.trimmed();

    QString jsonPath = QString(":/tests/test%1/variant%2.json")
                        .arg(testNumber)
                        .arg(variantNum);

    // Загружаем вопросы из JSON файла
    loadQuestionsFromJson(jsonPath);

    // Запускаем таймер на 70 минут
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TestTemplateDialog::updateTimer);
    timer->start(1000);

    // Инициализация аудио компонентов
    musicPlayer = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/music/background1.mp3"));
    musicPlayer->setLoops(QMediaPlayer::Infinite);

    // Изначальное отображение текущей части теста и кнопок навигации
    showCurrentPart();
}

TestTemplateDialog::~TestTemplateDialog()
{
    if (musicPlayer) {
        musicPlayer->stop();
        // audioOutput удаляется вместе с musicPlayer, если он был создан с родителем
        // Если QAudioOutput был создан без родителя, его нужно удалить вручную:
        // delete musicPlayer->audioOutput();
        delete musicPlayer;
    }
    if (timer) {
        timer->stop();
        delete timer;
    }
}

// Настройка пользовательского интерфейса
void TestTemplateDialog::setupUI() {
    if (layout()) delete layout();

    // Основной горизонтальный layout с отступами
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20); // Отступы от краев экрана
    mainLayout->setSpacing(20); // Расстояние между тестом и навигацией

    // Устанавливаем светло-серый фон для всего диалога
    this->setStyleSheet("background-color: #F0F0F0;");

    // Первая часть: область с вопросами (слева)
    questionsWidget = new QWidget;
    questionsLayout = new QVBoxLayout(questionsWidget);
    questionsLayout->setAlignment(Qt::AlignTop);
    questionsLayout->setSpacing(20);
    questionsWidget->setStyleSheet("background-color: #E6F3FF;"); // Пастельный голубой цвет для теста

    // Настраиваем прокрутку для области вопросов
    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(questionsWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { border: 10px solid white; }"); // Белая рамка для теста

    // Добавляем область теста первой (слева)
    mainLayout->addWidget(scrollArea, 1);

    // Вторая часть: панель навигации (посередине)
    QFrame* navFrame = new QFrame;
    navFrame->setFrameShape(QFrame::StyledPanel);
    navFrame->setFixedWidth(250);
    navFrame->setStyleSheet("background-color: white;");

    QVBoxLayout* navLayout = new QVBoxLayout(navFrame);
    navLayout->setSpacing(10);

    // Таймер в тонкой красной рамке с уменьшенным шрифтом
    timerLabel = new QLabel("Оставшееся время: 01:10:00");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("border: 1px solid red; padding: 5px; color: black; font-size: 10pt;");
    navLayout->addWidget(timerLabel);

    // Заголовок навигации (крупный и жирный)
    QLabel* navTitle = new QLabel("<b><font size=\"5\">Навигация по тесту</font></b>");
    navTitle->setAlignment(Qt::AlignCenter);
    navTitle->setStyleSheet("color: black;");
    navLayout->addWidget(navTitle);

    // Добавляем элементы управления музыкой
    QFrame* musicFrame = new QFrame;
    musicFrame->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout* musicLayout = new QVBoxLayout(musicFrame);

    musicButton = new QPushButton;
    musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    musicButton->setToolTip("Включить/выключить музыку");
    musicButton->setFixedSize(32, 32);
    connect(musicButton, &QPushButton::clicked, this, &TestTemplateDialog::toggleMusic);

    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setFixedWidth(180);
    connect(volumeSlider, &QSlider::valueChanged, this, &TestTemplateDialog::adjustVolume);

    QHBoxLayout* musicControlsLayout = new QHBoxLayout;
    musicControlsLayout->addWidget(musicButton);
    musicControlsLayout->addWidget(volumeSlider);
    musicControlsLayout->addStretch();

    musicLayout->addLayout(musicControlsLayout);
    navLayout->addWidget(musicFrame);

    // Кнопки навигации по вопросам
    QWidget* buttonsWidget = new QWidget;
    navButtonsLayout = new QGridLayout(buttonsWidget);
    navButtonsLayout->setSpacing(5);
    navLayout->addWidget(buttonsWidget);

    // Кнопка завершения теста синим цветом без рамки
    finishButton = new QPushButton("Закончить попытку...");
    finishButton->setStyleSheet("QPushButton { color: #007BFF; font-size: 12pt; border: none; }");
    navLayout->addWidget(finishButton);
    navLayout->addStretch();

    connect(finishButton, &QPushButton::clicked, this, &TestTemplateDialog::finishTest);

    // Добавляем навигационную панель второй
    mainLayout->addWidget(navFrame, 0);

    // Создаем внешний скроллбар справа от навигации
    QScrollBar* externalScrollBar = new QScrollBar(Qt::Vertical, this);
    externalScrollBar->setFixedHeight(700);
    externalScrollBar->setStyleSheet(
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #F0F0F0;"
        "    width: 15px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #808080;"
        "    min-height: 100px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
    );

    // Синхронизируем внешний скроллбар с внутренним скроллом области вопросов
    connect(externalScrollBar, &QScrollBar::valueChanged, [this](int value) {
        if (scrollArea && scrollArea->verticalScrollBar()) {
            scrollArea->verticalScrollBar()->setValue(value);
        }
    });

    connect(scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged,
            externalScrollBar, &QScrollBar::setRange);
    connect(scrollArea->verticalScrollBar(), &QScrollBar::valueChanged,
            externalScrollBar, &QScrollBar::setValue);

    // Добавляем внешний скроллбар последним (справа)
    mainLayout->addWidget(externalScrollBar);

    // Кнопки для перехода между частями теста
    nextPartButton = new QPushButton("Следующая страница", this);
    prevPartButton = new QPushButton("Предыдущая страница", this);

    // Стилизация кнопок навигации
    QString navButtonStyle = "QPushButton { color: #007BFF; font-size: 12pt; border: none; text-align: left; }";
    nextPartButton->setStyleSheet(navButtonStyle);
    prevPartButton->setStyleSheet(navButtonStyle);

    // Добавляем кнопки в нижнюю часть теста
    QHBoxLayout* navButtonsLayout = new QHBoxLayout;
    navButtonsLayout->addWidget(prevPartButton);
    navButtonsLayout->addWidget(nextPartButton);
    navButtonsLayout->addStretch();
    questionsLayout->addLayout(navButtonsLayout);

    connect(nextPartButton, &QPushButton::clicked, this, &TestTemplateDialog::goToNextPart);
    connect(prevPartButton, &QPushButton::clicked, this, &TestTemplateDialog::goToPrevPart);

    nextPartButton->setVisible(false);
    prevPartButton->setVisible(false);
}

// Загрузка вопросов из JSON файла
void TestTemplateDialog::loadQuestionsFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Файл с вопросами не найден: " + filename);
        QTimer::singleShot(0, this, SLOT(close()));
        return;
    }

    // Читаем и парсим JSON
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray arr = doc.array();

    // Очищаем предыдущие вопросы
    part1Questions.clear();
    part2Questions.clear();
    part1Info.clear();
    part2Info.clear();

    // Обрабатываем каждое задание из JSON
    int part = 0; // 0 - Часть 1, 1 - Часть 2
    bool hasPart2 = false;
    for (const QJsonValue& v : arr) {
        QJsonObject obj = v.toObject();
        QString type = obj["type"].toString();

        // Обработка информационного блока
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

        // Создаем виджет для вопроса
        QuestionWidget qw;
        qw.type = type;
        QFrame* frame = new QFrame;
        frame->setFrameShape(QFrame::StyledPanel);
        QVBoxLayout* vbox = new QVBoxLayout(frame);
        QLabel* qLabel = new QLabel(obj["question"].toString());
        qLabel->setWordWrap(true);
        vbox->addWidget(qLabel);
        qw.widget = frame;

        // Создаем элементы ввода в зависимости от типа вопроса
        if (type == "input") {
            // Простой ввод
            QLineEdit* edit = new QLineEdit;
            vbox->addWidget(edit);
            qw.edits.append(edit);
            qw.correct = obj["correct_answer"].toString();
        } else if (type == "registers") {
            // Ввод значений регистров
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
            // Создание таблицы
            int rows = obj["rows"].toInt();
            QJsonArray columnsArr = obj["columns"].toArray();
            QStringList columns;
            for (const QJsonValue& col : columnsArr)
                columns << col.toString();
            QTableWidget* table = new QTableWidget(rows, columns.size());
            table->setHorizontalHeaderLabels(columns);

            // Условное отображение вертикальных заголовков
            if (currentTestType == TestType::Mov) { // Только для Теста 2
                table->verticalHeader()->setVisible(true);
                table->setVerticalHeaderLabels(QStringList() << "00h" << "10h" << "20h" << "30h" << "40h" << "50h" << "60h" << "70h");
            } else { // Для Теста 1 и других
                table->verticalHeader()->setVisible(false);
            }

            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            table->verticalHeader()->setDefaultSectionSize(30);
            table->setMinimumHeight(rows * 30 + 40); // Высота таблицы
            vbox->addWidget(table);

            // Настройка ячеек таблицы
            QVector<QVector<TableCell>> tableEdits(rows, QVector<TableCell>(columns.size()));
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < columns.size(); ++c) {
                    QLineEdit* edit = new QLineEdit;
                    edit->setReadOnly(false);
                    edit->setAlignment(Qt::AlignCenter); // Выравнивание текста в центре
                    table->setCellWidget(r, c, edit);
                    tableEdits[r][c] = {edit, false};
                }
            }
            qw.tableEdits = tableEdits;

            // Загрузка правильных ответов для таблицы
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
        }

        // Добавляем виджет вопроса в соответствующую часть
        if (part == 0) {
            part1Questions.append(qw);
        } else {
            part2Questions.append(qw);
        }
    }

    // Показываем/скрываем кнопки навигации между частями
    nextPartButton->setVisible(hasPart2);
    prevPartButton->setVisible(false); // Всегда начинаем с первой части, кнопка назад не видна
}

// Подсчет баллов за тест
void TestTemplateDialog::calculateScore() {
    double totalScore = 0.0;
    double maxScore = 8.0; // Максимальный балл за тест

    results.clear(); // Очищаем старые результаты перед новым расчетом

    if (currentTestType == TestType::Mov) { // Тест 2: 40 заданий, каждое по 0.2 балла
        int totalQuestionsCounted = 40;
        double perQuestionScore = maxScore / totalQuestionsCounted; // 8.0 / 40 = 0.2 балла за задание

        auto scoreQuestions = [&](const QVector<QuestionWidget>& questions, int partNum) {
            for (int qIndex = 0; qIndex < questions.size(); ++qIndex) {
                const auto& qw = questions[qIndex];
                if (!qw.widget) {
                    continue;
                }

                bool allCorrect = true;
                QString questionText = qw.widget->findChild<QLabel*>()->text();
                QString userAnswer = "";

                if (qw.type != "table") {
                    if (!qw.edits.isEmpty()) {
                        QStringList userEdits;
                        for (int i = 0; i < qw.edits.size(); ++i) {
                            QString userText = qw.edits[i]->text().trimmed();
                            if (!userText.isEmpty()) { // Добавляем только непустые ответы для отображения
                                userEdits.append(userText);
                            }
                            if (i >= qw.corrects.size()) { // Защита от выхода за границы corrects
                                allCorrect = false; // Нет правильного ответа для сравнения
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
                        allCorrect = true; // Для информационных блоков или вопросов без полей ввода
                        userAnswer = ""; // Пустая строка, если нет ответа
                    }
                } else { // type == "table" for TestType::Mov (Test 2)
                    QStringList tableUserAnswers;
                    for (const auto& ta : qw.tableAnswers) {
                        if (ta.row < qw.tableEdits.size() && ta.col < qw.tableEdits[ta.row].size()) { // Защита от выхода за границы
                            if (!qw.tableEdits[ta.row][ta.col].isFixed) { // Учитываем только незафиксированные ячейки
                                QString cellText = qw.tableEdits[ta.row][ta.col].edit->text().trimmed();
                                if (!cellText.isEmpty()) { // Добавляем только непустые ячейки для отображения
                                    tableUserAnswers.append(QString("[%1,%2]:%3").arg(ta.row).arg(ta.col).arg(cellText));
                                }
                                if (cellText.toUpper() != ta.correct.toUpper()) {
                                    allCorrect = false;
                                }
                            }
                        } else {
                            allCorrect = false; // Ошибка в данных таблицы, считаем неверным
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

    } else { // Для других тестов (Test 1: SystemSch и т.д.)
        // Тест 1: Баллы распределяются по индивидуальным заполняемым элементам.
        // Результат для таблицы будет выводиться как одна запись за всю таблицу.

        int totalIndividualFillableItems = 0; // Для расчета perIndividualItemScore (по всему тесту)

        // Фаза 1: Подсчитываем общее количество индивидуальных заполняемых элементов во всем тесте
        auto countFillableItems = [&](const QVector<QuestionWidget>& questions) {
            for (const auto& qw : questions) {
                if (!qw.widget) {
                    continue;
                }
                if (qw.type == "input") {
                    totalIndividualFillableItems += 1;
                } else if (qw.type == "registers") {
                    totalIndividualFillableItems += qw.edits.size();
                } else if (qw.type == "table") {
                    for (const auto& ta : qw.tableAnswers) {
                        if (ta.row < qw.tableEdits.size() && ta.col < qw.tableEdits[ta.row].size() && !qw.tableEdits[ta.row][ta.col].isFixed) {
                            totalIndividualFillableItems++;
                        }
                    }
                }
            }
        };

        countFillableItems(part1Questions);
        countFillableItems(part2Questions);

        // Балл за каждый индивидуальный заполняемый элемент
        double perIndividualItemScore = (totalIndividualFillableItems > 0) ? maxScore / totalIndividualFillableItems : 0.0;

        // Фаза 2: Подсчет баллов и заполнение results
        auto scoreAndLogItems = [&](const QVector<QuestionWidget>& questions, int partNum) {
            for (int qIndex = 0; qIndex < questions.size(); ++qIndex) {
                const auto& qw = questions[qIndex];
                if (!qw.widget) {
                    continue;
                }
                QString baseQuestionText = qw.widget->findChild<QLabel*>()->text();
                double currentQuestionScore = 0.0;
                QString currentQuestionUserAnswer = "";
                double currentQuestionMaxScore = 0.0; // Максимальный балл для этой конкретной записи (вопроса/таблицы)

                if (qw.type == "input") {
                    currentQuestionMaxScore = perIndividualItemScore; // Макс. балл за 1 input = балл за 1 элемент
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
                        if (i >= qw.corrects.size() || qw.corrects[i].isEmpty()) {
                             continue;
                        }
                        totalRegsInQuestion++;
                        QString userRegText = qw.edits[i]->text().trimmed();
                        if (!userRegText.isEmpty()) {
                            userRegAnswers.append(userRegText);
                        }
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
                                if (!cellText.isEmpty()) {
                                    userTableAnswers.append(QString("[%1,%2]:%3").arg(ta.row).arg(ta.col).arg(cellText));
                                }
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

                totalScore += currentQuestionScore;
                results.append(ResultEntry{baseQuestionText, currentQuestionUserAnswer, currentQuestionScore, currentQuestionMaxScore, partNum});
            }
        };

        scoreAndLogItems(part1Questions, 1);
        scoreAndLogItems(part2Questions, 2);
    }

    // Сохраняем время
    QTime endTime = QTime::currentTime();
    int secs = startTime.secsTo(endTime);
    QString timeSpent = QString("%1:%2:%3")
        .arg(secs/3600, 2, 10, QChar('0'))
        .arg((secs%3600)/60, 2, 10, QChar('0'))
        .arg(secs%60, 2, 10, QChar('0'));

    // Показываем диалог с результатами
    ResultsDialog dlg(results, totalScore, timeSpent, currentUserName, this); // Передаем results и userName
    dlg.exec();
    emit testFinished();
    accept();
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
        info->setStyleSheet("background-color: #E6F3FF; padding: 10px;");
        questionsLayout->addWidget(info);
    }

    // Добавляем вопросы
    const QVector<QuestionWidget>& questions = (currentPart == 0 ? part1Questions : part2Questions);
    for (const auto& qw : questions) {
        if (qw.widget) questionsLayout->addWidget(qw.widget); // Проверяем, что виджет существует
    }

    // Кнопки перехода между частями только если есть обе части
    if (!part2Questions.isEmpty()) {
        // Убедимся, что кнопки добавлены в layout в правильном порядке
        if (currentPart == 0) {
            if (questionsLayout->indexOf(nextPartButton) == -1) {
                questionsLayout->addWidget(nextPartButton);
            }
            nextPartButton->setVisible(true);
            prevPartButton->setVisible(false);
        } else {
            if (questionsLayout->indexOf(prevPartButton) == -1) {
                questionsLayout->addWidget(prevPartButton);
            }
            prevPartButton->setVisible(true);
            nextPartButton->setVisible(false);
        }
    } else {
        nextPartButton->setVisible(false);
        prevPartButton->setVisible(false);
    }

    questionsLayout->addStretch();
    updateNavButtons(); // Обновляем кнопки навигации по вопросам

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

void TestTemplateDialog::createNavigationButtons() {
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
        navBtn->setStyleSheet(
            "QPushButton {"
            "    border: 2px solid black;" // Жирная черная рамка
            "    background-color: white;"
            "    color: black;"
            "    font-weight: bold;"
            "    font-size: 14pt;" // Увеличенный размер шрифта для цифр
            "    margin: 2px;"
            "}"
            "QPushButton:checked {"
            "    background-color: #007BFF;"
            "    color: white;"
            "}"
        );
        connect(navBtn, &QPushButton::clicked, this, [this, i]() {
            QWidget* w = (currentPart == 0 ? part1Questions[i].widget : part2Questions[i].widget);
            if (w) { // Проверяем, что виджет существует
                w->setFocus();
                if (scrollArea) {
                    QPoint relPos = w->mapTo(questionsWidget, QPoint(0, 0));
                    scrollArea->verticalScrollBar()->setValue(relPos.y());
                }
            }
        });
        navButtons.append(navBtn);
        int row = i / 4;
        int col = i % 4;
        navButtonsLayout->addWidget(navBtn, row, col);
    }
}

void TestTemplateDialog::updateNavButtons() {
    // Очищаем старые кнопки
    QLayoutItem* child;
    while ((child = navButtonsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }
    navButtons.clear(); // Очищаем вектор navButtons

    const QVector<QuestionWidget>& currentQuestions = (currentPart == 0) ? part1Questions : part2Questions;
    int row = 0;
    int col = 0;
    for (int i = 0; i < currentQuestions.size(); ++i) {
        QPushButton* navBtn = new QPushButton(QString::number(i + 1)); // Создаем новые кнопки
        navBtn->setCheckable(true);
        navBtn->setAutoExclusive(true);
        navBtn->setFixedSize(40, 40);
        navBtn->setStyleSheet("QPushButton { margin: 2px; }");
        connect(navBtn, &QPushButton::clicked, this, [this, i]() {
            QWidget* w = (currentPart == 0 ? part1Questions[i].widget : part2Questions[i].widget);
            if (w) { // Проверяем, что виджет существует
                w->setFocus();
                if (scrollArea) {
                    QPoint relPos = w->mapTo(questionsWidget, QPoint(0, 0));
                    scrollArea->verticalScrollBar()->setValue(relPos.y());
                }
            }
        });
        navButtons.append(navBtn); // Добавляем кнопку в вектор
        navButtonsLayout->addWidget(navBtn, row, col);
        col++;
        if (col >= 4) { // Максимум 4 кнопки в ряду
            col = 0;
            row++;
        }
    }

    // Обновляем видимость кнопок перехода между частями
    nextPartButton->setVisible(currentPart == 0 && !part2Questions.isEmpty());
    prevPartButton->setVisible(currentPart == 1);
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
    // Показываем диалог подтверждения с русскими кнопками "Да" и "Нет"
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы точно уверены, что хотите завершить тест?");

    // Добавляем кнопки с русским текстом
    QPushButton* yesButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton* noButton = msgBox.addButton("Нет", QMessageBox::NoRole);

    msgBox.setDefaultButton(yesButton); // Устанавливаем кнопку "Да" по умолчанию

    msgBox.exec(); // Показываем диалог и ждем выбора пользователя

    if (msgBox.clickedButton() != yesButton) {
        return; // Пользователь отменил завершение (нажал "Нет")
    }

    timer->stop();
    if (musicPlayer && musicPlayer->playbackState() == QMediaPlayer::PlayingState) {
        musicPlayer->stop(); // Останавливаем музыку при завершении теста
    }
    calculateScore();
    accept();
}

void TestTemplateDialog::toggleMusic()
{
    if (isMusicPlaying) {
        musicPlayer->pause();
        musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    } else {
        musicPlayer->play();
        musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    isMusicPlaying = !isMusicPlaying;
}

void TestTemplateDialog::adjustVolume(int value)
{
    if (musicPlayer && musicPlayer->audioOutput()) {
        musicPlayer->audioOutput()->setVolume(value / 100.0); // Громкость от 0.0 до 1.0
    }
}
