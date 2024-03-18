#include "chooselevelscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "QDebug"
#include "playscene.h"
#include "QSound"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    // 1. set background
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("Chooselevel");
    this->setParent(parent);

    // 2. set menu bar
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("Start");
    QAction * quitAction = startMenu->addAction("Exit");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    // 3. set back button
    QSound *backSound = new QSound(":/res/BackButtonSound.wav");
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        backSound->play();
        QTimer::singleShot(280, [=](){
           emit backToMainWindow();
        });
    });

    // 4. set level icon
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav");
    for (int i = 0; i < 20; ++i) {
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(25 + i%4 * 70, 130 + i/4 * 70);

        connect(btn, &MyPushButton::clicked, [=](){
            qDebug() << "choose " << i + 1;
            chooseSound->play();

            this->hide();
            level = new PlayScene(i, this);
            level->show();

            connect(level, &PlayScene::backToChooseWindow, [=](){
//                level->hide();
                // core need to delete level
                delete level;
                level = nullptr;
                this->show();
            });

        });

        QLabel *label = new QLabel();
        label->setParent(this);
        label->setFixedSize(btn->width(), btn->height());
        label->setText(QString::number(i + 1));
        label->move(25 + i%4 * 70, 130 + i/4 * 70);

        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // core set mouseevent transparent
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) / 2, 30, pix.width(), pix.height(), pix);
}
