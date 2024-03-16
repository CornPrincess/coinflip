#include "playscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"

PlayScene::PlayScene(int level_id, QWidget *parent) : QMainWindow(parent)
{
    // 1. set background
    this->setParent(parent);
    this->_level_id = level_id;

    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    QString str = QString("level_%1").arg(level_id + 1);
    this->setWindowTitle(str);

    // 2. set menu bar
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("Start");
    QAction * quitAction = startMenu->addAction("Exit");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    // 3. set back button
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        QTimer::singleShot(280, [=](){
           emit backToChooseWindow();
        });
    });

    // 4. set level label
    QLabel *label = new QLabel();
    label->setParent(this);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(20);
    label->setFont(font);
    QString str2 = QString("Level: %1").arg(level_id + 1);
    label->setText(str2);
    label->setGeometry(30, this->height() - 50, 120, 50);
}

void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) / 2, 30, pix.width(), pix.height(), pix);
}
