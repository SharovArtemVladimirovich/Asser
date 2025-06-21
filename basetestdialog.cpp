//Чтобы музыка была, нужно скачать пакеты: apt-get install qt5(или 6)-multimedia-devel
#include "basetestdialog.h"
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

// =================================================================
// КОНСТРУКТОР КЛАССА
// Вызывается один раз при создании окна теста.
// =================================================================

BaseTestDialog::BaseTestDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent)
    : QDialog(parent), timeLeft(70*60), currentTestType(testType), currentVariant(variant),
      currentUserName(userName), currentPart(0), isMusicPlaying(false)
{
    setWindowTitle(QString("Тест - Вариант %1").arg(variant));
    resize(1100, 700);

    startTime = QTime::currentTime();

    // 1. Создание всего интерфейса
    setupUI();

    // 2. Определение пути к файлу с вопросами
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

    QString variantNum = variant;
    variantNum.remove("Вариант");
    variantNum = variantNum.trimmed();

    QString jsonPath = QString(":/tests/test%1/variant%2.json")
                        .arg(testNumber)
                        .arg(variantNum);

    // 3. Загрузка вопросов из файла
    loadQuestionsFromJson(jsonPath);

    // 4. Запуск таймера
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BaseTestDialog::updateTimer);
    timer->start(1000);

    // 5. Настройка музыкального плеера
    musicPlayer = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/music/Мрачный_день.mp3"));
    musicPlayer->setLoops(QMediaPlayer::Infinite);
    // 6. Отображение первой части теста
    showCurrentPart();
}

// =================================================================
// ДЕСТРУКТОР
// Вызывается при закрытии окна. Останавливает плеер и таймер.
// =================================================================

BaseTestDialog::~BaseTestDialog()
{
    if (musicPlayer) {
        musicPlayer->stop();
        delete musicPlayer;
    }
    if (timer) {
        timer->stop();
        delete timer;
    }
}

// =================================================================
// SETUP UI - НАСТРОЙКА ИНТЕРФЕЙСА
// Создает все виджеты, кнопки, панели и расставляет их по окну.
// =================================================================

void BaseTestDialog::setupUI() {
    if (layout()) delete layout();

    // Главный горизонтальный слой: [ Область прокрутки с вопросами ] [ Правая панель навигации ] [ Внешний скроллбар ]
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);
    this->setStyleSheet("background-color: #F0F0F0;");
// --- Левая часть: Область с вопросами ---
    questionsWidget = new QWidget;
    questionsLayout = new QVBoxLayout(questionsWidget);
    questionsLayout->setAlignment(Qt::AlignTop);
    questionsLayout->setSpacing(20);
    questionsWidget->setStyleSheet("background-color: #E6F3FF;");
// --- Центральная часть: Панель навигации ---
    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(questionsWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { border: 10px solid white; }");

    mainLayout->addWidget(scrollArea, 1);

    QFrame* navFrame = new QFrame;
    navFrame->setFrameShape(QFrame::StyledPanel);
    navFrame->setFixedWidth(250);
    navFrame->setStyleSheet("background-color: white;");

    QVBoxLayout* navLayout = new QVBoxLayout(navFrame);
    navLayout->setSpacing(10);
// Таймер
    timerLabel = new QLabel("Оставшееся время: 01:10:00");
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet("border: 1px solid red; padding: 5px; color: black; font-size: 10pt;");
    navLayout->addWidget(timerLabel);
// Заголовок "Навигация"
    QLabel* navTitle = new QLabel("<b><font size=\"5\">Навигация по тесту</font></b>");
    navTitle->setAlignment(Qt::AlignCenter);
    navTitle->setStyleSheet("color: black;");
    navLayout->addWidget(navTitle);
// Блок управления музыкой
    QFrame* musicFrame = new QFrame;
    musicFrame->setFrameShape(QFrame::StyledPanel);
    QVBoxLayout* musicLayout = new QVBoxLayout(musicFrame);

    musicButton = new QPushButton;
    musicButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    musicButton->setToolTip("Включить/выключить музыку");
    musicButton->setFixedSize(32, 32);
    connect(musicButton, &QPushButton::clicked, this, &BaseTestDialog::toggleMusic);

    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);
    volumeSlider->setFixedWidth(180);
    connect(volumeSlider, &QSlider::valueChanged, this, &BaseTestDialog::adjustVolume);

    QHBoxLayout* musicControlsLayout = new QHBoxLayout;
    musicControlsLayout->addWidget(musicButton);
    musicControlsLayout->addWidget(volumeSlider);
    musicControlsLayout->addStretch();

    musicLayout->addLayout(musicControlsLayout);
    navLayout->addWidget(musicFrame);
 // Сетка для кнопок навигации (1, 2, 3...)
    QWidget* buttonsWidget = new QWidget;
    navButtonsLayout = new QGridLayout(buttonsWidget);
    navButtonsLayout->setSpacing(5);
    navLayout->addWidget(buttonsWidget);
// Кнопка "Закончить попытку"
    finishButton = new QPushButton("Закончить попытку...");
    finishButton->setStyleSheet("QPushButton { color: #007BFF; font-size: 12pt; border: none; }");
    navLayout->addWidget(finishButton);
    navLayout->addStretch();

    connect(finishButton, &QPushButton::clicked, this, &BaseTestDialog::finishTest);

    mainLayout->addWidget(navFrame, 0);
// --- Правая часть: Внешний (видимый) скроллбар ---
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
        "    background-color: #808080;"
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

// Связываем внешний скроллбар с внутренним (невидимым)
    connect(scrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, externalScrollBar, &QScrollBar::setRange);
    mainLayout->addWidget(externalScrollBar);
// --- Кнопки "Следующая/Предыдущая страница" (внизу области с вопросами) ---
    nextPartButton = new QPushButton("Следующая страница", this);
    prevPartButton = new QPushButton("Предыдущая страница", this);

    QString navButtonStyle = "QPushButton { color: #007BFF; font-size: 12pt; border: none; text-align: left; }";
    nextPartButton->setStyleSheet(navButtonStyle);
    prevPartButton->setStyleSheet(navButtonStyle);

    QHBoxLayout* navButtonsLayout_ = new QHBoxLayout;

    navButtonsLayout_->addWidget(prevPartButton);
    navButtonsLayout_->addWidget(nextPartButton);
    navButtonsLayout_->addStretch();
    questionsLayout->addLayout(navButtonsLayout_);

    connect(nextPartButton, &QPushButton::clicked, this, &BaseTestDialog::goToNextPart);
    connect(prevPartButton, &QPushButton::clicked, this, &BaseTestDialog::goToPrevPart);

    nextPartButton->setVisible(false);
    prevPartButton->setVisible(false);
}
// =================================================================
// ЗАГРУЗКА ВОПРОСОВ ИЗ JSON
// Читает файл и создает виджеты для каждого вопроса.
// =================================================================
void BaseTestDialog::loadQuestionsFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Файл с вопросами не найден: " + filename);
        QTimer::singleShot(0, this, SLOT(close()));
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray arr = doc.array();
// Очищаем старые вопросы
    part1Questions.clear();
    part2Questions.clear();
    part1Info.clear();
    part2Info.clear();

    int part = 0;
    bool hasPart2 = false;
// Проходим по каждому элементу в JSON
    for (const QJsonValue& v : arr) {
        QJsonObject obj = v.toObject();
        QString type = obj["type"].toString();
//Если это информационный блок, а не вопрос
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
        qLabel->setStyleSheet("font-weight: bold; color: #111; font-size: 13px;");
        qLabel->setWordWrap(true);
        vbox->addWidget(qLabel);
        qw.widget = frame;
// Определяем тип вопроса и создаем нужные поля для ввода
        if (type == "input") {
            QLineEdit* edit = new QLineEdit;
            QString correctAnswer = obj["correct_answer"].toString();
            int minWidth = 40;
            int maxWidth = 1000;
            int width = minWidth;
            if (!correctAnswer.isEmpty()) {
                width = correctAnswer.length() * 13 + 18;
                if (width < minWidth) width = minWidth;
                if (width > maxWidth) width = maxWidth;
                edit->setFixedWidth(width);
            }
            edit->setStyleSheet("background: white; border-radius: 6px; padding: 4px 10px; border: 1.5px solid #bdbdbd;");
            vbox->addWidget(edit);
            qw.edits.append(edit);
            qw.correct = correctAnswer;
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
                int minWidth = 40;
                int maxWidth = 1000;
                int width = minWidth;
                if (!correct.isEmpty()) {
                    width = correct.length() * 13 + 18;
                    if (width < minWidth) width = minWidth;
                    if (width > maxWidth) width = maxWidth;
                    regEdit->setFixedWidth(width);
                } else {
                    regEdit->setFixedWidth(60);
                }
                regEdit->setStyleSheet("background: white; border-radius: 6px; padding: 4px 10px; border: 1.5px solid #bdbdbd;");
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

            if (currentTestType == TestType::Mov) {
                table->verticalHeader()->setVisible(true);
                table->setVerticalHeaderLabels(QStringList() << "00h" << "10h" << "20h" << "30h" << "40h" << "50h" << "60h" << "70h");
            } else {
                table->verticalHeader()->setVisible(false);
            }

            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            table->verticalHeader()->setDefaultSectionSize(30);
            table->setMinimumHeight(rows * 30 + 40);
            vbox->addWidget(table);

            QVector<QVector<TableCell>> tableEdits(rows, QVector<TableCell>(columns.size()));
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < columns.size(); ++c) {
                    QLineEdit* edit = new QLineEdit;
                    edit->setReadOnly(false);
                    edit->setAlignment(Qt::AlignCenter);
                    edit->setStyleSheet("background: white;");
                    table->setCellWidget(r, c, edit);
                    tableEdits[r][c] = {edit, false};
                }
            }
            qw.tableEdits = tableEdits;

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
// Добавляем созданный вопрос в нужную часть теста
        if (part == 0) {
            part1Questions.append(qw);
        } else {
            part2Questions.append(qw);
        }
    }

    nextPartButton->setVisible(hasPart2);
    prevPartButton->setVisible(false);
}
// =================================================================
// ОТОБРАЖЕНИЕ ТЕКУЩЕЙ ЧАСТИ
// Очищает область вопросов и добавляет в нее виджеты для текущей части.
// =================================================================

void BaseTestDialog::showCurrentPart() {
    // 1. Полностью очищаем область вопросов
    QLayoutItem* child;
    while ((child = questionsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->setParent(nullptr);
        delete child;
    }
// 2. Добавляем информационный текст (если он есть)
    QString infoText = (currentPart == 0 ? part1Info : part2Info);
    if (!infoText.isEmpty()) {
        QLabel* info = new QLabel(infoText);
        info->setWordWrap(true);
        info->setStyleSheet("background-color: #E6F3FF; padding: 10px;");
        questionsLayout->addWidget(info);
    }
// 3. Добавляем виджеты всех вопросов для текущей части
    const QVector<QuestionWidget>& questions = (currentPart == 0 ? part1Questions : part2Questions);
    for (const auto& qw : questions) {
        if (qw.widget) questionsLayout->addWidget(qw.widget);
    }
// 4. Добавляем кнопки "Следующая/Предыдущая страница"

    if (!part2Questions.isEmpty()) {
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
// 5. Обновляем кнопки навигации (1, 2, 3...)
    updateNavButtons();
// 6. Прокручиваем в самый верх
    QTimer::singleShot(0, [this]() {
        if (scrollArea && scrollArea->verticalScrollBar()) {
            scrollArea->verticalScrollBar()->setValue(0);
        }
    });
}

void BaseTestDialog::goToNextPart() {
    if (currentPart == 0 && !part2Questions.isEmpty()) {
        currentPart = 1;
        showCurrentPart();
    }
}

void BaseTestDialog::goToPrevPart() {
    if (currentPart == 1) {
        currentPart = 0;
        showCurrentPart();
    }
}
// =================================================================
// ОБНОВЛЕНИЕ КНОПОК НАВИГАЦИИ
// Создает заново кнопки (1, 2, 3...) для текущей части теста.
// =================================================================
void BaseTestDialog::updateNavButtons() {
    QLayoutItem* child;
    while ((child = navButtonsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }
    navButtons.clear();

    const QVector<QuestionWidget>& currentQuestions = (currentPart == 0) ? part1Questions : part2Questions;
    int row = 0;
    int col = 0;
    for (int i = 0; i < currentQuestions.size(); ++i) {
        QPushButton* navBtn = new QPushButton(QString::number(i + 1));
        navBtn->setCheckable(true);
        navBtn->setAutoExclusive(true);
        navBtn->setFixedSize(45, 55);
        navBtn->setStyleSheet(
            "QPushButton {"
            "    border: 1px solid black;"
            "    background-color: white;"
            "    color: black;"
            "    font-weight: normal;"
            "    font-size: 12pt;"
            "    margin: 2px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:checked {"
            "    border: 3px solid black;"
            "    background-color: white;"
            "    color: black;"
            "    font-weight: bold;"
            "    font-size: 14pt;"
            "}"
        );
        connect(navBtn, &QPushButton::clicked, this, [this, i]() {
            selectedNavButtonIndex = i;
            QWidget* w = (currentPart == 0 ? part1Questions[i].widget : part2Questions[i].widget);
            if (w) {
                w->setFocus();
                if (scrollArea) {
                    QPoint relPos = w->mapTo(questionsWidget, QPoint(0, 0));
                    scrollArea->verticalScrollBar()->setValue(relPos.y());
                }
            }
        });
        if (i == selectedNavButtonIndex) {
            navBtn->setChecked(true);
        }
        navButtons.append(navBtn);
        navButtonsLayout->addWidget(navBtn, row, col);
        col++;
        if (col >= 4) {
            col = 0;
            row++;
        }
    }

    nextPartButton->setVisible(currentPart == 0 && !part2Questions.isEmpty());
    prevPartButton->setVisible(currentPart == 1);
}
// =================================================================
// ОБНОВЛЕНИЕ ТАЙМЕРА
// Вызывается каждую секунду, чтобы обновить текст таймера.
// =================================================================
void BaseTestDialog::updateTimer() {
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

// =================================================================
// СНЯТИЕ ВЫДЕЛЕНИЯ
// Убирает жирное выделение со всех кнопок навигации.
// =================================================================

void BaseTestDialog::clearNavButtonSelection() {
    selectedNavButtonIndex = -1;
    for (QPushButton* btn : navButtons) {
        if (btn->isChecked()) {
            btn->setChecked(false);
        }
    }
}
// =================================================================
// ЗАВЕРШЕНИЕ ТЕСТА
// Показывает диалог подтверждения и завершает тест.
// =================================================================

void BaseTestDialog::finishTest() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы точно уверены, что хотите завершить тест?");

    QPushButton* yesButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton* noButton = msgBox.addButton("Нет", QMessageBox::NoRole);

    msgBox.setDefaultButton(yesButton);

    msgBox.exec();

    if (msgBox.clickedButton() != yesButton) {
        return;
    }

    timer->stop();
    if (musicPlayer && musicPlayer->playbackState() == QMediaPlayer::PlayingState) {
        musicPlayer->stop();
    }
    calculateScore();
    accept();
}

void BaseTestDialog::toggleMusic()
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

void BaseTestDialog::adjustVolume(int value)
{
    if (musicPlayer && musicPlayer->audioOutput()) {
        musicPlayer->audioOutput()->setVolume(value / 100.0);
    }
}

void BaseTestDialog::calculateScore() {}
