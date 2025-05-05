#include "manuals.h"
#include "ui_manuals.h"
#include "style.h"

Manuals::Manuals(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manuals)
{
    ui->setupUi(this);
    ui -> widget -> setStyleSheet (ManualsST::StyleM);

    connect(ui -> MainBackButton, &QPushButton::clicked, this, &Manuals::showMainReq);
    connect(ui -> intelDocsButton, &QPushButton::clicked, this, &Manuals::openIntelDocs);
    connect(ui -> assemblyTutorialButton, &QPushButton::clicked, this, &Manuals::openAssemblyTutorial);
    connect(ui -> downloadCheatsheetButton, &QPushButton::clicked, this, &Manuals::downloadCheatsheet);

    connect(ui -> assemblyTutorialButton, &QPushButton::clicked, [this]() {
            emit showNotificationRequested("QLabel {image: url(:/imagesManuals/images/Asser_ML_Notification.png);}");
        });
}

Manuals::~Manuals()
{
    delete ui;
}

void Manuals::openIntelDocs()
{
    QDesktopServices::openUrl(QUrl("https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html"));
}

void Manuals::openAssemblyTutorial()
{
    QDesktopServices::openUrl(QUrl("https://www.academia.edu/5397239/%D0%A1%D0%BA%D0%BB%D1%8F%D1%80%D0%BE%D0%B2_%D0%98_%D0%98%D0%B7%D1%83%D1%87%D0%B0%D0%B5%D0%BC_Assembler_%D0%B7%D0%B0_7_%D0%B4%D0%BD%D0%B5%D0%B9_2010_"));
}

void Manuals::downloadCheatsheet()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить шпаргалку"), "",
        tr("PDF файлы (*.pdf);;Все файлы (*)"));

        if (fileName.isEmpty())
            return;

        if (QFile::copy(":/docs/docs/assembly_cheatsheet.pdf", fileName)) {
            QMessageBox::information(this, "Успех", "Файл успешно сохранен!");
        } else {
            QFile file(":/docs/docs/assembly_cheatsheet.pdf");
            QMessageBox::warning(this, "Ошибка",
            QString("Не удалось сохранить файл!\nФайл существует: %1\nОшибка: %2")
            .arg(file.exists() ? "Да" : "Нет")
            .arg(file.errorString()));
        }
}
