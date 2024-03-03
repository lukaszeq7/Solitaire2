#include <random>
#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent),
          _numberOfDecksOfCards(1),
          _numberOfFullCardsPerColor(13),
          _sampleCard(new Card("h", 1)),
          _xPosStack(-700),
          _yPosStack(-400),
          _hSpace(120),
          _vSpace(40)
{
    setupBoard();

    initCards(_numberOfDecksOfCards);
    spreadCards();
}

Board::~Board()
{
    delete _sampleCard;
    qDeleteAll(_freeStackCards);
    qDeleteAll(_cards);
}

void Board::setupBoard()
{
    setSceneRect(_sampleCard->boundingRect());
}

void Board::initCards(int numberOfDecksOfCards)
{
    for(int i = 0; i < _numberOfFullCardsPerColor; i++)
    {
        Card* freeStackCard = new Card("freeStack");
        addItem(freeStackCard);
        _freeStackCards.append(freeStackCard);
    }

    for (int i = 0; i < numberOfDecksOfCards; i++)
    {
        for(int value = 1; value <= _numberOfFullCardsPerColor; value++)
        {
            Card* card1 = new Card("h", value);
            _cards.append(card1);
            addItem(card1);

            Card* card2 = new Card("d", value);
            _cards.append(card2);
            addItem(card2);

            Card* card3 = new Card("s", value);
            _cards.append(card3);
            addItem(card3);

            Card* card4 = new Card("c", value);
            _cards.append(card4);
            addItem(card4);
        }
    }
}

void Board::spreadCards()
{
    int columnsCount = 13;
    int rowsCount = _numberOfDecksOfCards * 4;

    shuffleCards();

    for(int col = 0; col < columnsCount; col++)
    {
        Card* freeStackCard = _freeStackCards[col];
        freeStackCard->setStackNum(col);
        freeStackCard->setRowNum(0);
        freeStackCard->setZValue(-1);
        freeStackCard->setPos(_xPosStack + col * _hSpace, _yPosStack);
    }

    int cardIndex = 0;
    for(int col = 0; col < columnsCount; col++)
    {
        QList<Card*> stack;
        for(int row = 0; row < rowsCount; row++)
        {
            if (cardIndex < _cards.size())
            {
                Card* card = _cards[cardIndex];
                card->setStackNum(col);
                card->setRowNum(row);
                card->setZValue(row);
                card->setPos(_xPosStack + col * _hSpace, _yPosStack + row * _vSpace);

                stack.append(card);
                cardIndex++;
            }
        }
        _stacks.append(stack);
    }
}

void Board::shuffleCards()
{
    std::default_random_engine rng(std::random_device{}());
    std::shuffle(_cards.begin(), _cards.end(), rng);
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem*> itemsAtPosition = items(event->scenePos());
        QList<Card*> cardsUnderMouse = cardsAtPosition(itemsAtPosition);
        if(!cardsUnderMouse.isEmpty())
        {
            if(cardsUnderMouse.first()->color() == "freeStack")
            {
                return;
            }

            _srcCardStackNum = cardsUnderMouse.first()->stackNum();
            _srcCardRowNum = cardsUnderMouse.first()->rowNum();
            _selectedCards = selectedCards(_srcCardStackNum, _srcCardRowNum);

            pickUpTheCards(_selectedCards, _srcCardStackNum);
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!_selectedCards.isEmpty())
        {
            destroyItemGroup(_cardGroup);

            QList<QGraphicsItem *> itemsAtPosition = items(event->scenePos());
            QList<Card*> cardsUnderMouse = cardsAtPosition(itemsAtPosition);
            _destCardStackNum = cardsUnderMouse.last()->stackNum();
            bool isReleasedOnFreeStack = false;
            if(cardsUnderMouse.count() == 2 && cardsUnderMouse.last()->color() == "freeStack")
            {
                isReleasedOnFreeStack = true;
            }

            if(cardsUnderMouse.count() <= 1)
            {
                layDownTheCards(_selectedCards, _srcCardStackNum);
            }
            else
            {
                if(isSelectedCardsPositionable(isReleasedOnFreeStack))
                {
                    layDownTheCards(_selectedCards, _destCardStackNum);
                    collectCardsIfInOrder(_destCardStackNum);
                }
                else
                {
                    layDownTheCards(_selectedCards, _srcCardStackNum);
                }
            }
            _selectedCards.clear();
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

QList<Card *> Board::cardsAtPosition(const QList<QGraphicsItem *>& itemsAtPosition)
{
    QList<Card*> cardsAtPosition;
    for(QGraphicsItem* item : itemsAtPosition)
    {
        if(item->type() == _sampleCard->type())
        {
            Card* card = dynamic_cast<Card*>(item);
            cardsAtPosition.append(card);
        }
    }
    return cardsAtPosition;
}

QList<Card *> Board::selectedCards(int stackNum, int rowNum)
{
    QList<Card*> selectedCards;
    QList<Card*> stackCards = _stacks[stackNum];
    int stackSize = stackCards.count();
    for (int i = rowNum; i < stackSize; i++)
    {
        Card* card = stackCards[i];
        card->setZValue(200 + i);
        selectedCards.append(card);
    }
    return selectedCards;
}

bool Board::isSelectedCardsPositionable(bool isReleaseOnFreeStack)
{
    if(isReleaseOnFreeStack)
    {
        return true;
    }

    Card* lastStackCard = _stacks[_destCardStackNum].last();
    Card* firstSelectedCard = _selectedCards.first();
    if(isCardsInOrder(lastStackCard, firstSelectedCard))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Board::pickUpTheCards(QList<Card*>& selectedCards, int stackNum)
{
    if(!isSelectedCardsMoveable())
    {
        selectedCards.clear();
        updateCardsData(stackNum);
        return;
    }
    else
    {
        _cardGroup = new QGraphicsItemGroup();
        addCardsToGroup(selectedCards);

        removeCardsFromStack(selectedCards, stackNum);
        updateCardsData(stackNum);
    }
}

void Board::layDownTheCards(const QList<Card *> &selectedCards, int stackNum)
{
    setCardsOnPositions(selectedCards, stackNum);
    appendCardsToStack(selectedCards, stackNum);
    updateCardsData(stackNum);
}

bool Board::isSelectedCardsMoveable()
{
    Card* previousCard = _selectedCards[0];

    for(int i = 1; i < _selectedCards.count(); i++)
    {
        Card* card = _selectedCards[i];
        if(isCardsInOrder(previousCard, card) && isSameColor(previousCard, card))
        {
            previousCard = card;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Board::updateCardsData(int stackNum)
{
    int stackSize = _stacks[stackNum].count();
    for (int i = 0; i < stackSize; i++)
    {
        Card* card = _stacks[stackNum][i];
        card->setStackNum(stackNum);
        card->setRowNum(i);
        card->setZValue(i);
    }
}

void Board::addCardsToGroup(const QList<Card *>& selectedCards)
{
    for(Card* card : selectedCards)
    {
        _cardGroup->addToGroup(card);
    }
    addItem(_cardGroup);
    _cardGroup->setFlag(QGraphicsItemGroup::ItemIsMovable);
    _cardGroup->setZValue(200);
}

void Board::removeCardsFromStack(const QList<Card*>& selectedCards, int stackNum)
{
    for (int i = 0; i < selectedCards.count(); i++)
    {
        _stacks[stackNum].removeLast();
    }
}

void Board::setCardsOnPositions(QList<Card*> selectedCards, int stackNum)
{
    if(_stacks[stackNum].isEmpty())
    {
        qDebug() << "1";

        for (int i = 0; i < selectedCards.count(); i++)
        {
            Card *card = selectedCards[i];
            card->setX(_xPosStack + stackNum * _hSpace);
            card->setY(_yPosStack + i * _vSpace);
            card->setZValue(i);
        }
    }
    else
    {
        int lastCardInStack = _stacks[stackNum].count() - 1;
        Card *lastCard = _stacks[stackNum][lastCardInStack];
        for (int i = 0; i < selectedCards.count(); i++)
        {
            Card *card = selectedCards[i];
            card->setX(lastCard->x());
            card->setY(lastCard->y() + _vSpace + i * _vSpace);
            card->setZValue(lastCard->zValue() + i + 1);
        }
    }
}

void Board::appendCardsToStack(const QList<Card*>& selectedCards, int stackNum)
{
    for (int i = 0; i < selectedCards.count(); i++)
    {
        _stacks[stackNum].append(_selectedCards[i]);
    }
}

void Board::collectCardsIfInOrder(int stackNum)
{
    if(isCardsRemoveable(stackNum))
    {
        collectCards(stackNum);
    }
}

bool Board::isCardsRemoveable(int stackNum)
{
    int stackSize = _stacks[stackNum].count();
    if(_stacks[stackNum].last()->value() != 1 || stackSize < _numberOfFullCardsPerColor)
    {
        return false;
    }

    int orderCounter = 1;
    Card* previousCard = _stacks[stackNum].last();

    while(orderCounter < _numberOfFullCardsPerColor)
    {
        int i = stackSize - orderCounter - 1;
        Card* card = _stacks[stackNum][i];
        if(isCardsInOrder(card, previousCard) && isSameColor(card, previousCard))
        {
            previousCard = card;
            orderCounter++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Board::collectCards(int stackNum)
{
    int row = _stacks[stackNum].count() - 1;
    int i = 0;
    while(i < _numberOfFullCardsPerColor)
    {
        _stacks[stackNum][row]->hide();
        _stacks[stackNum].removeAt(row);

        row--;
        i++;
    }
    updateCardsData(stackNum);
}

bool Board::isCardsInOrder(Card *firstCard, Card *secondCard)
{
    return firstCard->value() == secondCard->value() + 1;
}

bool Board::isSameColor(Card *firstCard, Card *secondCard)
{
    return firstCard->color() == secondCard->color();
}

void Board::showCardsData(const QList<Card *>& cardList, const QString& text)
{
    for(Card* card : cardList)
    {
        qDebug() << text << card->color() << card->value() << "stack:" << card->stackNum() << "row:" << card->rowNum() << "z:" << card->zValue();
    }
}