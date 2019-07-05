#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"university.h"
#include<QPainter>
#include<QPaintEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ActionTimer();

private:
    Ui::MainWindow *ui;
    University* university;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
