#ifndef TEST2_H
#define TEST2_H

#include "basetestdialog.h"

class Test2 : public BaseTestDialog
{
    Q_OBJECT
public:
    explicit Test2(const QString& variant, const QString& userName, QWidget* parent = nullptr);

protected:
    void calculateScore() override;
};

#endif // TEST2_H
