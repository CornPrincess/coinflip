#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level_id, QWidget *parent = nullptr);

    // overwrite paintEnvent, draw window backgroud
    void paintEvent(QPaintEvent *);

    void judge();

signals:
    void backToChooseWindow();

private:
    int _level_id;
    int _coin_id_array[4][4];
    Coin* _coin_btn_array[4][4];
};

#endif // PLAYSCENE_H
