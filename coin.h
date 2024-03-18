#ifndef COIN_H
#define COIN_H

#include "QPushButton"
#include "QTimer"

class Coin : public QPushButton
{
    Q_OBJECT
public:
    explicit Coin(QString btn_img, QWidget *parent = nullptr);

    void setX(int x) {
        this->_x = x;
    }

    void setY(int y) {
        this->_y = y;
    }

    void setFlag(int flag) {
        this->_flag = flag;
    }

    void setCanFlip(bool value) {
        this->_can_flip = value;
    }

    int getX() const {
        return _x;
    }

    int getY() const {
        return _y;
    }

    bool getFlag() const {
        return _flag;
    }

    void flip();

    void mousePressEvent(QMouseEvent *e);

signals:
    void finishFlip();

private:
    void setIconByImageStr(QString str);

private:
    QString _btn_img;

    int _min = 1;

    int _max = 8;

    int _x;

    int _y;

    bool _flag;

    bool _can_flip = true;;

    QTimer* _timer;

};

#endif // COIN_H
