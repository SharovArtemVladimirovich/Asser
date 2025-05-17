#ifndef TESTTEMPLATEDIALOG_H
#define TESTTEMPLATEDIALOG_H

#include "testtype.h"


#include <QDialog>
#include <QLineEdit>

class TestTemplateDialog : public QDialog {
    Q_OBJECT
public:
    explicit TestTemplateDialog(TestType testType, const QString& variant, const QString& userName, QWidget *parent = nullptr);
    // ...
private:
    TestType currentTestType;
    QString currentVariant;
    QString currentUserName;
    // ...
    void loadQuestions(); // Загружает вопросы в зависимости от testType и variant
    QList<QPair<QLineEdit*, QString>> inputAnswers;
    void finishTest();

signals:
    void testFinished();
};

#endif // TESTTEMPLATEDIALOG_H
