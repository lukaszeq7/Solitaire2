#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _view(new QGraphicsView(this)),
        _scene(new QGraphicsScene(this)),
        _vSpace(60),
        _hSpace(200)
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
            card->setPos(-200 + column * _hSpace, -100 + row * _vSpace);
            card->setPosition(card->x(), card->y());
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
    int stackNumber = cardPressed->stackNumber();
    int rowNumber = cardPressed->rowNumber();
    for(int i = rowNumber; i < _stacks[stackNumber].count(); i++)
    {
        Card* selectedCard = _stacks[stackNumber][i];
        _selectedCards.append(selectedCard);

//        selectedCard->setZValue(200 + i);
    }

    for(Card* card : _selectedCards)
    {
        qDebug() << "cardPressed" << card->color() << card->value() << card->stackNumber() << card->rowNumber();

    }

//    qDebug() << _scene->items()
    QList<Card*> cardsAtPosition = stackItemsToCards(_selectedCards[0]->x());

    for(Card* card : cardsAtPosition)
    {
        qDebug() << "cardatposition" << card->color() << card->value()
        << "stack:" << card->stackNumber() << "row" << card->rowNumber();

    }

}

void MainWindow::onCardReleased(QList<Card*> cardsReleased)
{
    for(Card* card : cardsReleased)
    {
        qDebug() << "cardReleased" << card->color() << card->value();
    }
//    int stackNum = cardsReleased[0]->stackNumber();
//    qreal xPos = cardsReleased[1]->x();
//    qreal yPos = _stacks[stackNum][0]->y();

//    for(int i = 0; i < _selectedCards.count(); i++  )
//    {
//        Card* card = _selectedCards[i];
//        card->setPos(xPos, _vSpace);
//    }

    if(!_selectedCards.isEmpty())
    {
        _selectedCards.clear();
    }
}

QList<Card *> MainWindow::stackItemsToCards(qreal x)
{
    QList<Card*> cardsAtPosition;

    QList<QGraphicsItem*> items = _scene->items();
    for (QGraphicsItem* item : items)
    {
        if (item->x() == _selectedCards[0]->x())
        {
            Card* card = dynamic_cast<Card*>(item);
            cardsAtPosition.append(card);
        }
    }

    return cardsAtPosition;
}
