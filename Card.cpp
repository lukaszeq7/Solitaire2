#include "Card.h"

Card::Card(QGraphicsItem *parent) :
        QGraphicsItem(parent),
        _pixmapItem(new QGraphicsPixmapItem(this))
{
    QString imagePath(":/images/h1.png");
    QPixmap pixmap(imagePath);
    _pixmapItem->setPixmap(pixmap);
    _pixmapItem->setFlag(QGraphicsPixmapItem::ItemIsMovable);
}

Card::~Card()
{
}

QRectF Card::boundingRect() const
{
    return QRectF();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
