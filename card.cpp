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
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "******************************";
        qDebug() << "z:" << zValue();
        qDebug() << "pos:" << this->pos();
        qDebug() << "stack number:" << stackNumber();
        qDebug() << "row number:" << rowNumber();
    }
    QGraphicsObject::mousePressEvent(event);
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

