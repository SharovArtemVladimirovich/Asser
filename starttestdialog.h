#ifndef STARTTESTDIALOG_H
#define STARTTESTDIALOG_H


#pragma once
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class StartTestDialog : public QDialog {
    Q_OBJECT
public:
    StartTestDialog(QWidget *parent = nullptr, const QString& testName = "");
    void setTestName(const QString& name);
    QString selectedVariant() const;
    QString userName() const;

private:
    QComboBox *variantCombo;
    QLineEdit *nameEdit;
    QLabel *testNameLabel;
};

#endif // STARTTESTDIALOG_H
