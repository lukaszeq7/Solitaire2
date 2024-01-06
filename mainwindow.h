#ifndef SOLITAIRE2_MAINWINDOW_H
#define SOLITAIRE2_MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include "card.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    MainWindow::~MainWindow() override;

private:
    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QList<Card*> _cards;
    QList<Card*> _stacks;
};

#endif //SOLITAIRE2_MAINWINDOW_H
