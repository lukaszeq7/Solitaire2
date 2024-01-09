#include "card.h"

Card::Card(QGraphicsItem* parent)
        : QGraphicsObject(parent),
        _pixmapItem(new QGraphicsPixmapItem(this)),
        _stackNumber(-1),
        _rowNumber(-1)
{
    QPixmap pixmap(":/images/h1.png");
    _pixmapItem->setPixmap(pixmap);

    setFlag(QGraphicsItem::ItemIsMovable);
}

Card::~Card()
{
    delete _pixmapItem;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> itemsAtPosition = scene()->items(event->scenePos());
    for(auto item : itemsAtPosition)
    {
        if(item->type() == Card::type())
        {
            Card* cardItem = dynamic_cast<Card*>(item);
            qDebug() << cardItem->stackNumber();
        }
    }

    QGraphicsObject::mousePressEvent(event);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> itemsAtPosition = scene()->items(event->scenePos());
    for(auto item : itemsAtPosition)
    {
        if(item->type() == Card::type())
        {
            Card* cardItem = dynamic_cast<Card*>(item);
            qDebug() << cardItem->stackNumber();
        }
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

QRectF Card::boundingRect() const
{
    return _pixmapItem->boundingRect();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

int Card::stackNumber()
{
    return _stackNumber;
}

void Card::setStackNumber(int stackNumber)
{
    _stackNumber = stackNumber;
}

int Card::rowNumber()
{
    return _rowNumber;
}

void Card::setRowNumber(int rowNumber)
{
    _rowNumber = rowNumber;
    setZValue(rowNumber);
}

