#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPaintEvent"
#include "QPainter"
#include "mypushbutton.h"
#include "QDebug"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. set window background
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("CoinFlip");

    connect(ui->actionExit, &QAction::triggered, this, [=](){
        this->close();
    });

    chooseLevelSecne = new ChooseLevelScene(this);
    // listent to signal
    connect(chooseLevelSecne, &ChooseLevelScene::backToMainWindow, [=](){
        chooseLevelSecne->hide();
        this->show();
    });

    // 2. set start button
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5,
                   this->height() * 0.7);
    connect(startBtn, &MyPushButton::clicked, [=](){
        startBtn->zoom1();
        startBtn->zoom2();

        QTimer::singleShot(280, this, [=](){
            this->hide();
            chooseLevelSecne->show();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

