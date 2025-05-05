#include "mainwindow.h"

#include <QApplication>
#include <QLoggingCategory> //Библиотека для работы с выводом Логов



int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.gui.imageio=false"); //АХАХАХАХХАХАХ Я ЕМУ ЗАПРЕТИЛ ПОКАЗЫВАТЬ ПРЕДУПРЕЖДЕНИЕ О ТОМ, ЧТО КАРТИНКА БИТАЯ АХАХАХХАХАХАХ

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
