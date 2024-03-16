#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    // overwrite paintEnvent, draw window backgroud
    void paintEvent(QPaintEvent *);

signals:
    // back to mainwindow signal
    void backToMainWindow();

private:
    PlayScene *level = nullptr;

};

#endif // CHOOSELEVELSCENE_H
