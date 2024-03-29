#include "mypushbutton.h"
#include "QDebug"
#include "qpropertyanimation.h"

MyPushButton::MyPushButton() {}

MyPushButton::MyPushButton(QString normalImg, QString pressImg) {
    this->_noramlImg = normalImg;
    this->_pressImg = pressImg;

    QPixmap pix;
    if(!pix.load(normalImg)) {
        qDebug() << "load normalImg fail.";
        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::zoom1() {
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::zoom2() {
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e) {
    if (this->_pressImg != "") {
        QPixmap pix;
        if(!pix.load(_pressImg)) {
            qDebug() << "load _pressImg fail.";
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
    if (this->_noramlImg != "") {
        QPixmap pix;
        if(!pix.load(_noramlImg)) {
            qDebug() << "load _noramlImg fail.";
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
