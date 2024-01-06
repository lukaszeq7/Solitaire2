#include "card.h"

Card::Card(QGraphicsItem* parent)
        : QGraphicsObject(parent),
        _pixmapItem(new QGraphicsPixmapItem(this))
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
        qreal z = zValue();
        qDebug() << "z:" << z;
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

