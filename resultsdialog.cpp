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
    resize(1200, 700);
    this->setStyleSheet("background-color: #F0F0F0;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);

    // --- Основной фрейм ---
    QFrame* resultsContentFrame = new QFrame(this);
    resultsContentFrame->setStyleSheet("background-color: #D0E0F0; border: none; border-radius: 0px;");
    QVBoxLayout* contentLayout = new QVBoxLayout(resultsContentFrame);
    contentLayout->setContentsMargins(15, 15, 15, 15);
    contentLayout->setSpacing(8);

    // --- Сообщение ---
    QString congratsColor = (totalScore >= 4.0) ? "#1976d2" : "#c62828";
    QLabel* congratsMessage = new QLabel();
    congratsMessage->setAlignment(Qt::AlignCenter);
    congratsMessage->setWordWrap(true);
    congratsMessage->setStyleSheet("font-size:22px; font-weight:bold; margin-bottom:5px; background: transparent; color:" + congratsColor + ";");
    if (totalScore >= 4.0) {
        congratsMessage->setText(QString("Поздравляем, %1! Тест пройден!").arg(userName));
    } else {
        congratsMessage->setText(QString("%1, тест не пройден, но мы верим в вас!").arg(userName));
    }
    contentLayout->addWidget(congratsMessage);

    // --- Итоговый балл и время ---
    QString resultColor = (totalScore >= 4.0) ? "#1976d2" : "#c62828";
    QLabel* totalLabel = new QLabel(
        QString("<div style='font-size:26px; font-weight:bold; color:%1; text-align:center; margin-bottom:2px;'>"
                "Ваш результат: %2 из 8.00 баллов</div>"
                "<div style='font-size:18px; color:#607d8b; text-align:center; margin-top:4px;'>Затраченное время: %3</div>")
            .arg(resultColor)
            .arg(totalScore, 0, 'f', 2)
            .arg(timeSpent)
    );
    totalLabel->setAlignment(Qt::AlignCenter);
    totalLabel->setStyleSheet("background: transparent; margin-top: 5px; margin-bottom: 8px;");
    contentLayout->addWidget(totalLabel);

    // --- Прокручиваемая область ---
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(14);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scroll->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    // --- Части ---
    bool hasPart2 = false;
    for (const auto& entry : results) {
        if (entry.part == 2) { hasPart2 = true; break; }
    }
    int currentPart = 0;
    for (int i = 0; i < results.size(); ++i) {
        const auto& entry = results[i];
        if (hasPart2 && entry.part != currentPart) {
            currentPart = entry.part;
            QLabel* partLabel = new QLabel(QString("Часть %1").arg(currentPart));
            partLabel->setAlignment(Qt::AlignCenter);
            partLabel->setStyleSheet("font-size:18px; font-weight:bold; color: #1976d2; background-color: #D0E0F0; border: none; margin-top:10px; margin-bottom:8px;");
            scrollLayout->addWidget(partLabel);
        }
        // --- Блок задания ---
        QWidget* block = new QWidget;
        QVBoxLayout* blockLayout = new QVBoxLayout(block);
        blockLayout->setContentsMargins(16, 10, 16, 10);
        blockLayout->setSpacing(5);
        block->setStyleSheet("background: #f5f5f5; border-radius: 10px; margin-bottom: 10px; padding: 10px 18px;");
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(block);
        shadow->setBlurRadius(12);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 30));
        block->setGraphicsEffect(shadow);
        // Вопрос + балл
        QLabel* questionLabel = new QLabel(
            QString("<div style='font-size:17px; color:#222; font-weight:500; margin-bottom:2px;'>%1</div>"
                    "<div style='font-size:15px; color:#222; margin-top:4px;'>Балл: %2 из %3</div>")
                .arg(entry.question)
                .arg(entry.score, 0, 'f', 2)
                .arg(entry.maxScore, 0, 'f', 2)
        );
        questionLabel->setTextFormat(Qt::RichText);
        blockLayout->addWidget(questionLabel);
        // Ответ
        QString cleanedUserAnswer = entry.userAnswer.trimmed();
        QRegularExpression re("[a-zA-Z0-9А-Яа-я]");
        bool hasMeaningfulAnswer = !cleanedUserAnswer.isEmpty() && re.match(cleanedUserAnswer).hasMatch();
        QString answerTextContent;
        QLabel* userLabel = nullptr;
        QString answerColor;
        if (hasMeaningfulAnswer) {
            if (entry.score >= entry.maxScore && entry.maxScore > 0) {
                answerColor = "#2e7d32"; // зелёный
            } else if (entry.score > 0 && entry.score < entry.maxScore) {
                answerColor = "#ff9800"; // оранжевый
            } else {
                answerColor = "#c62828"; // красный
            }
            answerTextContent = QString("<span style='color:%1; font-weight:bold; border-bottom:2px solid %1;'>Ваш ответ:</span> %2").arg(answerColor, cleanedUserAnswer.toHtmlEscaped());
            userLabel = new QLabel(answerTextContent);
            userLabel->setStyleSheet(QString("font-size:15px; color:%1; background:transparent; font-weight:normal; margin-top:2px; border-bottom:2px solid %1;").arg(answerColor));
        } else {
            answerColor = "#c62828";
            answerTextContent = "<span style='color:#c62828; font-weight:bold; border-bottom:2px solid #c62828;'>Ответ не введен</span>";
            userLabel = new QLabel(answerTextContent);
            userLabel->setStyleSheet("font-size:14px; color:#c62828; background:transparent; font-weight:bold; margin-top:2px; border-bottom:2px solid #c62828;");
        }
        userLabel->setTextFormat(Qt::RichText);
        userLabel->setWordWrap(true);
        blockLayout->addWidget(userLabel);
        scrollLayout->addWidget(block);
    }
    scrollLayout->addStretch(1);
    scrollWidget->setLayout(scrollLayout);
    scroll->setWidget(scrollWidget);
    contentLayout->addWidget(scroll);
    mainLayout->addWidget(resultsContentFrame);
    // --- Кнопка закрытия ---
    QPushButton* closeBtn = new QPushButton("ЗАКРЫТЬ");
    closeBtn->setMinimumHeight(54);
    closeBtn->setMinimumWidth(240);
    closeBtn->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #D0E0F0, stop:1 #E6F3FF);"
        "    color: black;"
        "    font-weight: bold;"
        "    font-size: 14pt;"
        "    padding: 5px 15px;"
        "    border-radius: 3px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #B8D0E8, stop:1 #D0E0F0);"
        "}"
    );
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignHCenter);
}
