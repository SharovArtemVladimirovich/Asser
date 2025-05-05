#include "mainwindow.h"
#include "screenspace.h"
#include "style.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , stck(new QStackedWidget(this))
    , fullscreenBtn(new QPushButton(this))
{
    setupScreen();
    setupNotificationSystem();
    setCentralWidget(stck);
    setWindowTitle("Asser Turbo");
}

void MainWindow::setupScreen()
{
//---Скрин главный--------------------------------------

    MainScreen* mainScreen = new MainScreen(this); // Обьявляем здесь нас виджет
    stck -> addWidget(mainScreen); // Добавляем к стеку виджет

    connect(mainScreen, &MainScreen::showTestsReq, [this](){ // берем переменную mainScreen из MainScreen::showTestsReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::TESTS);// подключаем индекс из screenСПАЙС
    });

    connect(mainScreen, &MainScreen::showAuthorsReq, [this](){ // берем переменную mainScreen из MainScreen::showAuthorsReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::AUTHORS);// подключаем индекс из screenСПАЙС
    });

    connect(mainScreen, &MainScreen::showManualsReq, [this](){ // берем переменную mainScreen из MainScreen::showAuthorsReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::MANUALS);// подключаем индекс из screenСПАЙС
    });

//---Скрин тество---------------------------------------

    tests* testsScreen = new tests(this);
    stck -> addWidget(testsScreen); // Добавляем к стеку виджет

    connect(testsScreen, &tests::showMainReq, [this](){ //берем переменную testsScreen из tests::showMainReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::MAIN); // а именно подключаем индекс из screenСПАЙС
    });

//---Скрин авторов--------------------------------------

    authors *authorsScreen = new authors(this);
    stck -> addWidget(authorsScreen);

    connect(authorsScreen, &authors::showMainReq, [this](){ // берем переменную mainScreen из MainScreen::showMainReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::MAIN);// подключаем индекс из screenСПАЙС
    });

    connect(authorsScreen, &authors::showDonutReq, [this](){ // берем переменную mainScreen из MainScreen::showMainReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::DONUT);// подключаем индекс из screenСПАЙС
    });

//---Скрин донатов--------------------------------------

    Donut *donutScreen = new Donut(this);
    stck -> addWidget(donutScreen);

    connect(donutScreen, &Donut::showAuthorsReq, [this](){ // берем переменную mainScreen из MainScreen::showMainReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::AUTHORS);// подключаем индекс из screenСПАЙС
    });

//---Скрин мануалов-------------------------------------

    Manuals *manualsScreen = new Manuals(this);
    stck -> addWidget(manualsScreen);

    connect(manualsScreen, &Manuals::showMainReq, [this](){ // берем переменную mainScreen из MainScreen::showMainReq и меняем [ЗДЕСЬ]
        stck -> setCurrentIndex(Screen::MAIN);// подключаем индекс из screenСПАЙС
    });

    connect(manualsScreen, &Manuals::showNotificationRequested, this, &MainWindow::handleNotification);

//---Настройки кнопок-----------------------------------

    fullscreenBtn -> setCheckable(true); // Делаем ее ЧИКАБЕЛЬНОЙ
    fullscreenBtn -> setFixedSize(50, 70); // Задаем размеры кнопахи
    fullscreenBtn -> move(30, 30); // Позиция в левом верхнем углу
    fullscreenBtn->setParent(this); // Делаем кнопаху дочерней для главного окна
    fullscreenBtn->raise(); // Поднимаем поверх всех виджетов

    fullscreenBtn->setObjectName("fullscreenBtn");  // Устанавливаем имя ДО применения стилей
    fullscreenBtn -> setStyleSheet(GlobalST::FSButton);

    connect(fullscreenBtn, &QPushButton::clicked,  // Правильный сигнал
                this, &MainWindow::toggleFullscreen);
}


void MainWindow::switchWithAnim(int index){
    QPropertyAnimation *anim = new QPropertyAnimation(stck, "pos");
    anim -> setDuration(300);
    anim -> setStartValue(QPoint(width(), 0));
    anim -> setEndValue(QPoint(400, 0));
    anim -> setEasingCurve(QEasingCurve::OutQuad);

    connect(anim, &QPropertyAnimation::finished, [this, index](){
        stck -> setCurrentIndex(index);
    });

    anim -> start(QPropertyAnimation::DeleteWhenStopped);

}


void MainWindow::toggleFullscreen() {
    if (isFullscreen) {
        showNormal();
        setGeometry(normalGeometry);
        // Убираем фон при возврате в нормальный режим
        this->setStyleSheet("");
        fullscreenBtn -> move(30, 30); // Позиция в левом верхнем углу

    } else {
        normalGeometry = geometry();
        showFullScreen();
        fullscreenBtn -> move(675, 155); // Позиция в левом верхнем углу
        // Устанавливаем фон только для главного окна
        this->setStyleSheet(GlobalST::Background);
    }
    isFullscreen = !isFullscreen;
    fullscreenBtn->setChecked(isFullscreen);
}


void MainWindow::setupNotificationSystem() {
    notificationLabel = new QLabel(this);
    notificationLabel -> hide();
    notificationLabel -> setWordWrap(true);
    notificationLabel -> setFixedSize(300, 80);

    notificationTimer = new QTimer(this);
    notificationTimer->setSingleShot(true);

    connect(notificationTimer, &QTimer::timeout, [this]() {
        hideNotification();
    });

    connect(this, &MainWindow::showNotificationRequested,
            this, &MainWindow::handleNotification);
}

void MainWindow::handleNotification(const QString& message) {
    notificationLabel->setStyleSheet(message);
    showNotification();
}

void MainWindow::showNotification() {

    if (this -> isFullScreen()){
    notificationLabel -> move(30, 30);
    } else {
    notificationLabel -> move(30, 100);
    }

    notificationLabel->show();
    notificationLabel->raise();

    notificationTimer->start(5000); // Скрыть через 5 сек
}

void MainWindow::hideNotification() {
    notificationLabel->hide();
}

void MainWindow::goMain_clicked()
{
    switchWithAnim(Screen::MAIN);
}

void MainWindow::goTests_clicked()
{
    switchWithAnim(Screen::TESTS);
}

void MainWindow::goAuthors_clicked()
{
    switchWithAnim(Screen::AUTHORS);
}

void MainWindow::goDonut_clicked()
{
    switchWithAnim(Screen::DONUT);
}

void MainWindow::goManuals_clicked()
{
    switchWithAnim(Screen::MANUALS);
}

