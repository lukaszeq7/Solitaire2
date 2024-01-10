#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _view(new QGraphicsView(this)),
        _scene(new QGraphicsScene(this))
{
    for(int i = 9; i >= 1; i--)
    {
        Card* card = new Card("h", i);
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
            connect(card, &Card::cardPressed, this, &MainWindow::onCardPressed);
            connect(card, &Card::cardReleased, this, &MainWindow::onCardReleased);
            card->setStackNumber(column);
            card->setPos(-200 + column * 200, -100 + row * 70);
            card->setPosition(card->pos());
            card->setRowNumber(row);

            stack.append(card);
            _scene->addItem(card);

            cardIndex++;
        }
        _stacks.append(stack);
    }

    _view->setScene(_scene);
    _view->setSceneRect(_cards[0]->boundingRect());
    _view->setFixedSize(1200, 600);
}

MainWindow::~MainWindow()
{
    qDeleteAll(_cards);
}

void MainWindow::onCardPressed(Card* cardPressed)
{
    qDebug() << "cardPressed" << cardPressed->color() << cardPressed->value();
}

void MainWindow::onCardReleased(QList<Card*> cardsReleased)
{
    for(Card* card : cardsReleased)
    {
        qDebug() << "cardReleased" << card->color() << card->value();
    }
}