#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"
#include "QLabel"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level_id, QWidget *parent = nullptr);

    // overwrite paintEnvent, draw window backgroud
    void paintEvent(QPaintEvent *);

    void judge();

    void lockCoin();

    void unlockCoin();

signals:
    void backToChooseWindow();

private:
    int _level_id;
    int _coin_id_array[4][4];
    Coin* _coin_btn_array[4][4];
    QLabel * _win_label;
};

#endif // PLAYSCENE_H
