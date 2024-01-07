#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _view(new QGraphicsView(this)),
        _scene(new QGraphicsScene(this))
{
    for(int i = 0; i < 9; i++)
    {
        Card* card = new Card();
        _cards.append(card);
    }

    int cardIndex = 0;
    int columnCount = 3;
    int rowCount = 3;
    for(int column = 0; column < columnCount; column++)
    {
        QList<Card*> stack;
        for(int row = 0; row < rowCount; row++)
        {
            Card* card = _cards[cardIndex];
            card->setStackNumber(column);
            stack.append(card);
            _scene->addItem(card);
            cardIndex++;

            card->setPos(-200 + column * 200, -100 + row * 70);
            card->setZValue(row);
        }
        _stacks.append(stack);
    }
    qDebug() << _stacks[0];
    qDebug() << _stacks[1];
    qDebug() << _stacks[2];


    _view->setScene(_scene);
    _view->setSceneRect(_cards[0]->boundingRect());
    _view->setFixedSize(800, 600);
}

MainWindow::~MainWindow()
{
    qDeleteAll(_cards);
}