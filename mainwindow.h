#ifndef SOLITAIRE2_MAINWINDOW_H
#define SOLITAIRE2_MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Board.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Board* _board;
    QGraphicsView* _view;

    qreal _sceneWidth;
    qreal _sceneHeight;
};

#endif //SOLITAIRE2_MAINWINDOW_H
