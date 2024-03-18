#include "playscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "coin.h"
#include "dataconfig.h"
#include "QDebug"
#include "QPropertyAnimation"

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

    // 5. set coins
    DataConfig config;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            QLabel *label = new QLabel();
            QPixmap pix(":/res/BoardNode.png");
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(58 + i * 50, 200 + j * 50);

            QString coin_img;
            int coin_flag = config._data[this->_level_id][i][j];
            this->_coin_id_array[i][j] = coin_flag;

            if (coin_flag == 1) {
                coin_img = QString(":/res/Coin0001.png");
            } else if (coin_flag == 0) {
                coin_img = QString(":/res/Coin0008.png");
            } else {
                qDebug() << "Error, coin config is mess.";
            }
            Coin *coin = new Coin(coin_img, this);
            coin->setX(i);
            coin->setY(j);
            coin->setFlag(coin_flag);
            coin->move(60 + i * 50, 203 + j * 50);
            this->_coin_btn_array[i][j] = coin;

            // judege after coin flip
            connect(coin, &Coin::finishFlip, [=](){
                this->judge();
            });
            connect(coin, &QPushButton::clicked, [=](){
                this->_coin_id_array[i][j] = this->_coin_id_array[i][j] ? 0 : 1;
                coin->flip();
                // core lock other coin after flip
                lockCoin();

                // filp around coin
                int deltX[4] = {1, 0, -1, 0};
                int delty[4] = {0, 1, 0, -1};
                for (int i = 0; i < 4; i++) {
                    int x = coin->getX() + deltX[i];
                    int y = coin->getY() + delty[i];
                    if (x >= 0 && x < 4 && y >= 0 && y < 4) {
                        QTimer::singleShot(100, this, [=](){
                            auto cb = this->_coin_btn_array[x][y];
                            this->_coin_id_array[x][y] = this->_coin_id_array[x][y] ? 0 : 1;
                            cb->flip();
                        });
                    }
                }

                // judge whether win
//                this->judge();
            });
        }
    }

    // 6. set success image
    this->_win_label = new QLabel();
    QPixmap winPix;
    winPix.load(":/res/LevelCompletedDialogBg.png");
    this->_win_label->setGeometry(0, 0, winPix.width(), winPix.height());
    this->_win_label->setPixmap(winPix);
    this->_win_label->setParent(this);
    this->_win_label->move((this->width() - winPix.width()) / 2, -winPix.height());
}

void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) / 2, 30, pix.width(), pix.height(), pix);
}

void PlayScene::judge() {
    qDebug() << "start to judge";
    bool win = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!this->_coin_btn_array[i][j]->getFlag()) {
                win = false;
                break;
            }
        }
    }

    if (win) {
        qDebug() << "bingo!!!";
        lockCoin();
        // show win label
        QPropertyAnimation *animation = new QPropertyAnimation(this->_win_label, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(QRect(this->_win_label->x(), this->_win_label->y(),
                                       this->_win_label->width(), this->_win_label->height()));
        animation->setEndValue(QRect(this->_win_label->x(), this->_win_label->y() + 144,
                                       this->_win_label->width(), this->_win_label->height()));
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();
    } else {
        unlockCoin();
    }
}

void PlayScene::lockCoin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_coin_btn_array[i][j]->setCanFlip(false);
        }
    }
}

void PlayScene::unlockCoin() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->_coin_btn_array[i][j]->setCanFlip(true);
        }
    }
}
