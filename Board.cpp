#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent),
        _sampleCard(new Card("h", 1)),
        _hSpace(120),
        _vSpace(40)
{
    setSceneRect(_sampleCard->boundingRect());

    for (int i = 0; i < 1; i++)
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
        for(int row = 0; row < 4; row++)
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
//    int stackNum = -1;
    int rowNum = -1;
    _cardGroup = new QGraphicsItemGroup();
    QList<Card*> cardsAtPosition;
    QList<QGraphicsItem*> itemsAtPosition = items(event->scenePos());

    if(!itemsAtPosition.isEmpty())
    {
        int z = 200;
        for(auto item : itemsAtPosition)
        {
            if(item->type() == _sampleCard->type())
            {
                Card* card = dynamic_cast<Card*>(item);
                cardsAtPosition.append(card);
            }
        }
        _srcStackNum = cardsAtPosition[0]->stackNum();
        rowNum = cardsAtPosition[0]->rowNum();


        for (int i = rowNum; i < _stacks[_srcStackNum].count(); i++)
        {
            Card* card = _stacks[_srcStackNum][i];
            card->setZValue(200 + i);
            _cardGroup->addToGroup(card);
            _selectedCards.append(card);
        }
        addItem(_cardGroup);
        _cardGroup->setFlag(QGraphicsItemGroup::ItemIsMovable);
        _cardGroup->setZValue(200);
        for(Card* card : _selectedCards)
        {
            qDebug() << "selected cards" << card->color() << card->value() << "stack:" << card->stackNum() << "row:" << card->rowNum() << card->zValue();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    destroyItemGroup(_cardGroup);

    if(!_selectedCards.isEmpty())
    {
        int rowNum = -1;
        QList<Card *> cardsAtPosition;
        QList<QGraphicsItem *> itemsAtPosition = items(event->scenePos());

        if(itemsAtPosition.count() > 1)
        {

                for (auto item: itemsAtPosition)
                {
                    if (item->type() == _sampleCard->type())
                    {
                        Card *card = dynamic_cast<Card *>(item);
                        cardsAtPosition.append(card);
                        qDebug() << "cardatposition release" << card->color() << card->value() << card->zValue();
                    }
                }//TODO here, if there is 1 card drop to scene, app crashes, length == 1
                //set card source pos, and data
                _destStackNum = cardsAtPosition[1]->stackNum();
                rowNum = cardsAtPosition[1]->rowNum();
                qDebug() << "released" << _destStackNum << rowNum;

            int lastCardNum = _stacks[_destStackNum].count() - 1;
            Card *lastCard = _stacks[_destStackNum][lastCardNum];
            for (int i = 0; i < _selectedCards.count(); i++)
            {
                Card *card = _selectedCards[i];
                card->setX(lastCard->x());
                card->setY(lastCard->y() + _vSpace + i * _vSpace);
                card->setZValue(lastCard->zValue() + i + 1);

            }

            //update stacks data

            for (int i = 0; i < _selectedCards.count(); i++)
            {
                _stacks[_srcStackNum].removeLast();
            }

            int newRowIndex = _stacks[_destStackNum].count();
            for (int i = 0; i < _selectedCards.count(); i++)
            {
                _selectedCards[i]->setStackNum(_destStackNum);
                _selectedCards[i]->setRowNum(newRowIndex + i);

                _stacks[_destStackNum].append(_selectedCards[i]);

            }

            for (Card *card: _stacks[_srcStackNum])
            {
                qDebug() << "SRCstack" << card->color() << card->value() << "stack:" << card->stackNum() << "row:"
                         << card->rowNum();

            }

            for (Card *card: _stacks[_destStackNum])
            {
                qDebug() << "DESTstack" << card->color() << card->value() << "stack:" << card->stackNum() << "row:"
                         << card->rowNum();

            }
        }


        _srcStackNum = -1;
        _destStackNum = -1;
        _selectedCards.clear();

    }

    QGraphicsScene::mouseReleaseEvent(event);
}
