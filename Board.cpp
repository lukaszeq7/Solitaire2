#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent)
{
    setSceneRect(_card.boundingRect());

    for(int i = 0; i < 9; i++)
    {
        Card* card = new Card();
        _cards.append(card);
        addItem(card);
    }

    spreadCards();
}

Board::~Board()
{
    qDeleteAll(_cards);
}

void Board::spreadCards()
{
    int cardIndex = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            QList<Card*> stack;
            if (cardIndex < _cards.size())
            {
                Card* card = _cards[cardIndex];
//                _cardData->setStackNum(i);
//                _cardData->setRowNum(j);
                cardIndex++;

                stack.append(card);
            }
            _stacks.append(stack);
        }
    }
}

void Board::setCardStackNum(int cardStackNum)
{
    _cardData->setStackNum(cardStackNum);
}

int Board::cardStackNum() const
{
    return _cardData->stackNum();
}

void Board::setCardRowNum(int cardRowNum)
{
    _cardData->setRowNum(cardRowNum);
}

int Board::cardRowNum() const
{
    return _cardData->rowNum();
}