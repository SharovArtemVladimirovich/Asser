#ifndef TEST1_H
#define TEST1_H

#include "basetestdialog.h"

class Test1 : public BaseTestDialog
{
    Q_OBJECT
public:
    explicit Test1(const QString& variant, const QString& userName, QWidget* parent = nullptr);

protected:
    void calculateScore() override;
};

#endif // TEST1_H
