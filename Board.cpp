#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent),
        _sampleCard(new Card("h", 1)),
        _hSpace(200),
        _vSpace(60)
{

    setSceneRect(_sampleCard->boundingRect());

    for(int i = 1; i <= 9; i++)
    {
        Card* card = new Card("h", i);
        _cards.append(card);
        addItem(card);
    }

    spreadCards();
}

Board::~Board()
{
    delete _sampleCard;
    qDeleteAll(_cards);
}

void Board::spreadCards()
{
    int cardIndex = 0;
    for(int i = 0; i < 3; i++)
    {
        QList<Card*> stack;
        for(int j = 0; j < 3; j++)
        {
            if (cardIndex < _cards.size())
            {
                Card* card = _cards[cardIndex];
                card->setStackNum(i);
                card->setRowNum(j);
                card->setZValue(j);
                card->setPos(-200 + i * _hSpace, -100 + j * _vSpace);

                stack.append(card);
                cardIndex++;
            }
        }
        _stacks.append(stack);
    }

    for(auto stack : _stacks)
    {
        for(Card* card : stack)
        {
            qDebug() << card->color() << card->value() << "stack:" << card->stackNum() << "row:" << card->rowNum();
        }
    }
}