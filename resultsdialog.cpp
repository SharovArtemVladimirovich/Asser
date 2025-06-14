#include "resultsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpression>

ResultsDialog::ResultsDialog(const QVector<ResultEntry>& results, double totalScore, const QString& timeSpent, const QString& userName, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Результаты теста");
    resize(1200, 700); // Уменьшаем общий размер окна
    this->setStyleSheet("background-color: #F0F0F0;"); // Светло-серый фон для всего диалога результатов

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15); // Отступы от краев экрана
    mainLayout->setSpacing(15); // Расстояние между основными блоками

    // Основной фрейм для содержимого результатов (фон как у теста, БЕЗ ОБЩЕЙ РАМКИ)
    QFrame* resultsContentFrame = new QFrame(this);
    resultsContentFrame->setStyleSheet("background-color: #D0E0F0; border: none; border-radius: 0px;"); // Небесно-серый пастельный фон, без рамок
    QVBoxLayout* contentLayout = new QVBoxLayout(resultsContentFrame);
    contentLayout->setContentsMargins(15, 15, 15, 15); // Внутренние отступы внутри фрейма
    contentLayout->setSpacing(8); // Отступы между элементами внутри фрейма

    // Персонализированное сообщение о прохождении/непрохождении
    QLabel* congratsMessage = new QLabel();
    congratsMessage->setAlignment(Qt::AlignCenter);
    congratsMessage->setWordWrap(true);
    congratsMessage->setStyleSheet("font-size:20px; font-weight:bold; margin-bottom:5px; color: black; background: transparent;");

    if (totalScore >= 4.0) { // Если набрал половину или больше (4 из 8)
        congratsMessage->setText(QString("<span style='color:#2e7d32;'>Поздравляем, %1! Тест пройден!</span>").arg(userName));
    } else {
        congratsMessage->setText(QString("<span style='color:#c62828;'>%1, тест не пройден, но мы верим в вас!</span>").arg(userName));
    }
    contentLayout->addWidget(congratsMessage);


    // Итоговый балл и время
    QLabel* totalLabel = new QLabel(
        QString("<div style='font-size:22px; font-weight:bold; color:#2e7d32; text-align:center;'>"
                "Ваш результат: %1 из 8.00 баллов</div>"
                "<div style='font-size:13px; color:#555; text-align:center;'>Затраченное время: %2</div>")
            .arg(totalScore, 0, 'f', 2)
            .arg(timeSpent)
    );
    totalLabel->setAlignment(Qt::AlignCenter);
    totalLabel->setStyleSheet("background: transparent; margin-top: 5px; margin-bottom: 8px;");
    contentLayout->addWidget(totalLabel);

    // Прокручиваемая область для заданий
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(10); // Отступ между блоками заданий
    scrollLayout->setContentsMargins(0, 0, 0, 0); // Убираем внутренние маржины скролл-виджета
    scroll->setStyleSheet("QScrollArea { border: none; background: transparent; }"); // Убираем рамки у самой области прокрутки


    // Определяем, есть ли две части
    bool hasPart2 = false;
    for (const auto& entry : results) {
        if (entry.part == 2) { hasPart2 = true; break; }
    }

    // Добавляем задания по частям
    int currentPart = 0;
    for (int i = 0; i < results.size(); ++i) {
        const auto& entry = results[i];

        // Заголовок части (только если есть две части)
        if (hasPart2 && entry.part != currentPart) {
            currentPart = entry.part;
            QLabel* partLabel = new QLabel(QString("Часть %1").arg(currentPart));
            partLabel->setAlignment(Qt::AlignCenter);
            // На том же фоне, что и основной текст, без рамки и закруглений
            partLabel->setStyleSheet("font-size:16px; font-weight:bold; color: black; background-color: #D0E0F0; border: none; margin-top:10px; margin-bottom:8px;");
            scrollLayout->addWidget(partLabel);
        }

        // Блок задания (зеленый/красный фон, без рамки)
        QWidget* block = new QWidget;
        QVBoxLayout* blockLayout = new QVBoxLayout(block);
        blockLayout->setContentsMargins(15, 8, 15, 8); // Уменьшаем внутренние отступы блока
        blockLayout->setSpacing(3); // Уменьшаем расстояние между вопросом и полем ответа

        // Цвет фона блока задания
        QString blockBackgroundColor;
        if (entry.score >= entry.maxScore && entry.maxScore > 0) {
            blockBackgroundColor = "#b9f6ca"; // зеленый для полностью решенных
        } else if (entry.score > 0 && entry.score < entry.maxScore) {
            blockBackgroundColor = "#fff9c4"; // желтый для частично решенных (нейтральный)
        } else {
            blockBackgroundColor = "#ffb3b3"; // красный для нерешенных
        }

        block->setStyleSheet(QString(
            "background: %1;"
            "border-radius: 10px;" // Немного уменьшаем закругления
            "margin-bottom: 10px;" // Отступ между блоками заданий
            "padding: 8px 15px;" // Уменьшаем паддинг
            "border:  %1;" // УБИРАЕМ РАМКУ ВОКРУГ КАЖДОГО ЗАДАНИЯ
        ).arg(blockBackgroundColor));

        // Добавляем тень через QGraphicsDropShadowEffect
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(block);
        shadow->setBlurRadius(12); // Уменьшаем размытие тени
        shadow->setOffset(0, 3); // Уменьшаем смещение тени
        shadow->setColor(QColor(0, 0, 0, 30)); // Немного светлее тень
        block->setGraphicsEffect(shadow);

        // Вопрос + балл в одном блоке
        QLabel* questionLabel = new QLabel(
            QString("<div style='font-size:15px; color:#222; font-weight:normal;'>%1</div>" // Уменьшаем шрифт вопроса
                    "<div style='font-size:13px; color:black; margin-top:4px;'>Балл: %2 из %3</div>") // Уменьшаем шрифт балла, цвет черный
                .arg(entry.question)
                .arg(entry.score, 0, 'f', 2)
                .arg(entry.maxScore, 0, 'f', 2)
        );
        questionLabel->setTextFormat(Qt::RichText);
        blockLayout->addWidget(questionLabel);

        // Определяем цвет текста ответа
        QString userAnswerTextColor;
        if (entry.score >= entry.maxScore && entry.maxScore > 0) {
            userAnswerTextColor = "green"; // Зеленый текст, если правильный
        } else {
            userAnswerTextColor = "red"; // Красный текст, если неправильный или нет ответа
        }

        QString cleanedUserAnswer = entry.userAnswer.trimmed();
        QRegularExpression re("[a-zA-Z0-9А-Яа-я]");
        bool hasMeaningfulAnswer = !cleanedUserAnswer.isEmpty() && re.match(cleanedUserAnswer).hasMatch();

        QString answerTextContent;
        if (hasMeaningfulAnswer) {
            answerTextContent = "Ваш ответ: " + cleanedUserAnswer.toHtmlEscaped();
        } else {
            answerTextContent = "Ответ не введен";
        }

        // Стиль для QLabel, который будет содержать ответ (БЕЗ РАМОК, только цвет текста)
        QLabel* userLabel = new QLabel(answerTextContent);
        userLabel->setTextFormat(Qt::RichText);
        userLabel->setStyleSheet(
            QString("QLabel {"
                    "    font-size:14px;"
                    "    color:%1;" // Цвет текста ответа динамический
                    "    background: transparent;" // УБРАН ЛЮБОЙ ФОН
                    "    padding: 0px;" // Убираем паддинг, если текст не в рамке
                    "    margin: 0px;" // Убираем маржины
                    "}")
                .arg(userAnswerTextColor)
        );
        userLabel->setWordWrap(true);

        blockLayout->addWidget(userLabel);

        scrollLayout->addWidget(block);
    }

    scrollLayout->addStretch(1);
    scrollWidget->setLayout(scrollLayout);
    scroll->setWidget(scrollWidget);

    contentLayout->addWidget(scroll); // Добавляем QScrollArea в resultsContentFrame

    mainLayout->addWidget(resultsContentFrame); // Добавляем основной фрейм в главный layout

    // Крупная красивая кнопка закрытия
    QPushButton* closeBtn = new QPushButton("Закрыть");
    closeBtn->setMinimumHeight(45); // Уменьшаем высоту кнопки
    closeBtn->setMinimumWidth(180); // Уменьшаем ширину кнопки
    closeBtn->setStyleSheet(
        "font-size: 20px;" // Уменьшаем шрифт
        "background: #1976d2;"
        "color: white;"
        "border-radius: 10px;" // Немного уменьшаем закругления
        "padding: 10px 30px;" // Уменьшаем паддинг
        "font-weight: bold;"
        "border: none;"
    );
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignHCenter);
}
