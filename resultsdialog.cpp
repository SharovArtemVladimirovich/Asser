#include "resultsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>

ResultsDialog::ResultsDialog(const QVector<ResultEntry>& results, double totalScore, const QString& timeSpent, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Результаты теста");
    resize(1400, 800);
    this->setStyleSheet("background: #f4faff;"); // Приятный светло-голубой фон (можно заменить на свой)

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Итоговый балл и время
    QLabel* totalLabel = new QLabel(
        QString("<div style='font-size:26px; font-weight:bold; color:#2e7d32; text-align:center;'>"
                "Ваш результат: %1 из 8.00 баллов</div>"
                "<div style='font-size:15px; color:#555; text-align:center;'>Затраченное время: %2</div>")
            .arg(totalScore, 0, 'f', 2)
            .arg(timeSpent)
    );
    totalLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(totalLabel);

    // Прокручиваемая область для заданий
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

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
            partLabel->setStyleSheet("background:#cbe3fa; font-size:18px; font-weight:bold; padding:6px 12px; border-radius:8px; margin-top:10px; margin-bottom:8px;");
            scrollLayout->addWidget(partLabel);
        }

        // Блок задания
        QWidget* block = new QWidget;
        QVBoxLayout* blockLayout = new QVBoxLayout(block);
        blockLayout->setContentsMargins(16, 10, 16, 10);

        // Цвет балла
        QString scoreColor = (entry.score < entry.maxScore) ? "#ffb3b3" : "#b9f6ca"; // красный/зелёный фон
        QString scoreTextColor = (entry.score < entry.maxScore) ? "#c62828" : "#2e7d32";

        // Вопрос + балл в одном блоке
        QLabel* questionLabel = new QLabel(
            QString("<div style='font-size:16px; color:#222; font-weight:normal;'>%1</div>"
                    "<div style='font-size:14px; color:%2; margin-top:4px;'>Балл: %3 из %4</div>")
                .arg(entry.question)
                .arg(scoreTextColor)
                .arg(entry.score, 0, 'f', 2)
                .arg(entry.maxScore, 0, 'f', 2)
        );
        questionLabel->setTextFormat(Qt::RichText);

        // Ответ пользователя (если есть)
        QLabel* userLabel = nullptr;
        if (!entry.userAnswer.trimmed().isEmpty()) {
            userLabel = new QLabel("Ваш ответ: <i style='color:#888;'>" + entry.userAnswer.toHtmlEscaped() + "</i>");
            userLabel->setTextFormat(Qt::RichText);
            userLabel->setStyleSheet("font-size:13px; color:#888; margin-top:2px;");
        }

        block->setStyleSheet(QString(
            "background: %1;"
            "border-radius: 12px;"
            "margin-bottom: 14px;"
            "padding: 10px 18px;"
        ).arg(scoreColor));

        // Добавляем тень через QGraphicsDropShadowEffect
        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(block);
        shadow->setBlurRadius(16);
        shadow->setOffset(0, 4);
        shadow->setColor(QColor(0, 0, 0, 40));
        block->setGraphicsEffect(shadow);

        blockLayout->addWidget(questionLabel);
        if (userLabel) blockLayout->addWidget(userLabel);

        scrollLayout->addWidget(block);
    }

    scrollLayout->addStretch(1);
    scrollWidget->setLayout(scrollLayout);
    scroll->setWidget(scrollWidget);
    mainLayout->addWidget(scroll);

    // Крупная красивая кнопка закрытия
    QPushButton* closeBtn = new QPushButton("Закрыть");
    closeBtn->setMinimumHeight(56);
    closeBtn->setMinimumWidth(220);
    closeBtn->setStyleSheet(
        "font-size: 22px;"
        "background: #1976d2;"
        "color: white;"
        "border-radius: 14px;"
        "padding: 14px 40px;"
        "font-weight: bold;"
    );
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignHCenter);
}
