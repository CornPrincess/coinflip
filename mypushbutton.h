#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton();

    MyPushButton(QString normalImg, QString pressImg = "");

    void zoom1();

    void zoom2();

    // rewrite mouse event
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:

private:
    QString _noramlImg;
    QString _pressImg;

};

#endif // MYPUSHBUTTON_H
