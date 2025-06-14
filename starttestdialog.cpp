#include "starttestdialog.h"
#include "style.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>




StartTestDialog::StartTestDialog(QWidget *parent, const QString &testName) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    setWindowTitle(testName);

    //Вывод описания и других лабелов
    QLabel *opisanie = new QLabel(this);
    opisanie -> setText(TestsDialogST::Opisanie);
    opisanie -> setObjectName("opisanie");

    QLabel *labelVar = new QLabel(this);
    labelVar -> setText("Выберите вариант:");
    labelVar -> setObjectName("labelVar");

    QLabel *labelName = new QLabel(this);
    labelName -> setText("Введите имя:");
    labelName -> setObjectName("labelName");

    // Выбор варианта
    variantCombo = new QComboBox(this);
    variantCombo -> addItems({"Вариант 1", "Вариант 2", "Вариант 3"});
    variantCombo -> setObjectName("variantCombo");

    // Ввод имени
    nameEdit = new QLineEdit(this);
    nameEdit -> setPlaceholderText("Введите ваше имя");
    nameEdit -> setObjectName("nameEdit");

    // Кнопка "Поехали!"
    QPushButton *startBtn = new QPushButton("Поехали!", this);
    // connect(startBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(startBtn, &QPushButton::clicked, this, [this]() {
        QString name = nameEdit->text().trimmed();

        // Проверка длины
        if (name.length() < 2 || name.length() > 50) {
            QMessageBox::warning(this, "Ошибка", "Имя должно содержать от 2 до 50 символов!");
            return;
        }

        // Проверка на наличие минимум 2 букв
        int letterCount = 0;
        for (const QChar &c : name) {
            if (c.isLetter()) letterCount++;
        }
        if (letterCount < 2) {
            QMessageBox::warning(this, "Ошибка", "Имя должно содержать минимум 2 буквы!");
            return;
        }

        // Проверка на допустимые символы
        QString allowedSymbols = "@~$^+=-&#*:.№!";
        for (const QChar &c : name) {
            if (!c.isLetter() && !c.isDigit() && !allowedSymbols.contains(c)) {
                QMessageBox::warning(this, "Ошибка", "Имя содержит недопустимые символы! Разрешены только буквы, цифры и символы: @~$^+=-&#*:.№!");
                return;
            }
        }

        accept();
    });

    layout -> addWidget (opisanie);
    layout -> addWidget (labelVar);
    layout -> addWidget (variantCombo);
    layout -> addWidget (labelName);
    layout -> addWidget (nameEdit);
    layout -> addWidget (startBtn);
}

QString StartTestDialog::selectedVariant() const {
    return variantCombo -> currentText();
}

QString StartTestDialog::userName() const {
    return nameEdit->text();
}
