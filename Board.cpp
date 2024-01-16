#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent),
        _sampleCard(new Card("h", 1)),
        _hSpace(120),
        _vSpace(40)
{
    setSceneRect(_sampleCard->boundingRect());

    for (int i = 0; i < 2; i++)
    {
        for(int value = 1; value <= 13; value++)
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
    for(int col = 0; col < 13; col++)
    {
        QList<Card*> stack;
        for(int row = 0; row < 8; row++)
        {
            if (cardIndex < _cards.size())
            {
                Card* card = _cards[cardIndex];
                card->setStackNum(col);
                card->setRowNum(row);
                card->setZValue(row);
                card->setPos(-700 + col * _hSpace, -100 + row * _vSpace);

                stack.append(card);
                cardIndex++;
            }
        }
        _stacks.append(stack);
    }

//    for(auto stack : _stacks)
//    {
//        for(Card* card : stack)
//        {
//            qDebug() << card->color() << card->value() << "stack:" << card->stackNum() << "row:" << card->rowNum();
//        }
//    }
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _cardGroup = new QGraphicsItemGroup();
    QList<Card*> cardsAtPosition;
    QList<QGraphicsItem*> itemsAtPosition = items(event->scenePos());

    if(!itemsAtPosition.isEmpty())
    {
        for(auto item : itemsAtPosition)
        {
            if(item->type() == _sampleCard->type())
            {
                Card* card = dynamic_cast<Card*>(item);
                card->setFlag(QGraphicsItem::ItemIsMovable);
                _cardGroup->addToGroup(card);
                cardsAtPosition.append(card);
            }
        }
        qDebug() << "pressed" << cardsAtPosition[0]->color() << cardsAtPosition[0]->value() <<
                 cardsAtPosition[0]->stackNum() << cardsAtPosition[0]->rowNum();
    }
    addItem(_cardGroup);
    _cardGroup->setFlag(QGraphicsItemGroup::ItemIsMovable);

    QGraphicsScene::mousePressEvent(event);
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<Card*> cardsAtPosition;
    QList<QGraphicsItem*> itemsAtPosition = items(event->scenePos());

    if(!itemsAtPosition.isEmpty())
    {
        for(auto item : itemsAtPosition)
        {
            if(item->type() == _sampleCard->type())
            {
                Card* card = dynamic_cast<Card*>(item);
                cardsAtPosition.append(card);
            }
        }

        for (auto card : cardsAtPosition)
        {
            qDebug() << "released" << card->color() << card->value() << card->stackNum() << card->rowNum();
        }
    }
    destroyItemGroup(_cardGroup);

    QGraphicsScene::mouseReleaseEvent(event);
}
