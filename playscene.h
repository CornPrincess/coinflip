#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int level_id, QWidget *parent = nullptr);

    // overwrite paintEnvent, draw window backgroud
    void paintEvent(QPaintEvent *);

signals:
    void backToChooseWindow();

private:
    int _level_id;

};

#endif // PLAYSCENE_H
