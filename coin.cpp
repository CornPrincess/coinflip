#include "coin.h"
#include "QDebug"

Coin::Coin(QString btn_img, QWidget *parent) : QPushButton(parent)
{
    this->setIconByImageStr(btn_img);
    this->_timer = new QTimer(this);

    connect(_timer, &QTimer::timeout, [=](){
        if (_flag) {
            QString s = QString(":/res/Coin000%1.png").arg(_min++);
            this->setIconByImageStr(s);
            if (_min > _max) {
                _min = 1;
                _timer->stop();
                _flag = !_flag;
                qDebug() << "on to off finish";
                emit finishFlip();
           }
        } else {
            QString s = QString(":/res/Coin000%1.png").arg(_max--);
            this->setIconByImageStr(s);
            if (_min > _max) {
                _max = 8;
                _timer->stop();
                _flag = !_flag;
                qDebug() << "off to on finish";
                emit finishFlip();
           }
        }
    });
}

void Coin::flip() {
    this->_timer->start(30);
//    emit finishFlip();
//    _flag = !_flag;
}

void Coin::setIconByImageStr(QString str) {
    QPixmap pix;
    if (!pix.load(str)) {
        QString str = QString("coin load %1 image fail").arg(str);
        qDebug() << str;
        return;
    }
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void Coin::mousePressEvent(QMouseEvent *e) {
    // to make user can not flip coin
    if (!this->_can_flip) {
        return;
    }
    return QPushButton::mousePressEvent(e);
}
