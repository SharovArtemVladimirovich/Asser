#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainscreen.h"
#include "tests.h"
#include "authors.h"
#include "donut.h"
#include "manuals.h"

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void switchWithAnim(int index);
    void toggleFullscreen();
    void goMain_clicked();
    void goTests_clicked();
    void goAuthors_clicked();
    void goDonut_clicked();
    void goManuals_clicked();
    void handleNotification(const QString& message);
    void hideNotification();
    void showNotification();
    void handleTestRequest(TestType type, const QString& name, const QString& variant);

private:

    void setupScreen();
    void setupNotificationSystem();

    QStackedWidget *stck;

    MainScreen *mainScreen;
    tests *testsScreen;
    authors *authorsScreen;
    Donut *donutScreen;
    Manuals *manualsScreen;


    QLabel* notificationLabel;
    QTimer* notificationTimer;

    QPushButton *fullscreenBtn;
    bool isFullscreen = false;
    QRect normalGeometry;

signals:
    void showNotificationRequested(const QString& message);

};
#endif // MAINWINDOW_H
