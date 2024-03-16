#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // overwrite paintEnvent, draw window backgroud
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    ChooseLevelScene *chooseLevelSecne = nullptr;
};
#endif // MAINWINDOW_H
