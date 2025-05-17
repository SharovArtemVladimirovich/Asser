#include "starttestdialog.h"
#include "style.h"

#include <QVBoxLayout>
#include <QLabel>


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
    connect(startBtn, &QPushButton::clicked, this, &QDialog::accept);

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
