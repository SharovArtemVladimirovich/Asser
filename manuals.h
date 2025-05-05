#ifndef MANUALS_H
#define MANUALS_H

#include <QWidget>
#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Manuals;
}

class Manuals : public QWidget
{
    Q_OBJECT

public:
    explicit Manuals(QWidget *parent = nullptr);
    ~Manuals();

private slots:
    void openIntelDocs();
    void openAssemblyTutorial();
    void downloadCheatsheet();

private:
    Ui::Manuals *ui;

signals:
    void showMainReq();
    void showNotificationRequested(const QString& message);
};

#endif // MANUALS_H
