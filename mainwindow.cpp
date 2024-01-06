#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _view(new QGraphicsView(this)),
        _scene(new QGraphicsScene(this))
{
    for(int i = 0; i < 4; i++)
    {
        Card* card = new Card();
        _cards.append(card);
    }

    for(int i = 0; i < _cards.length(); i++)
    {
        Card* card = _cards[i];
        _scene->addItem(card);
        card->setPos(-200, -100 + i * 70);
        card->setZValue(i);
    }

    _view->setScene(_scene);
    _view->setSceneRect(_cards[0]->boundingRect());
    _view->setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    qDeleteAll(_cards);
    qDeleteAll(_stacks);
}