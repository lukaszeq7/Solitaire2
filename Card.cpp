#include "Card.h"

Card::Card(const QString &color, int value, QGraphicsItem *parent) :
        QGraphicsItem(parent),
        _color(color),
        _value(value),
        _pixmapItem(new QGraphicsPixmapItem(this))
{
    QString valueStr = QString::number(_value);
    QString imagePath(":/images/" + _color + valueStr + ".png");
    QPixmap pixmap(imagePath);
    _pixmapItem->setPixmap(pixmap);

//    setFlag(QGraphicsPixmapItem::ItemIsMovable);
}

Card::~Card()
{
}

QRectF Card::boundingRect() const
{
    return _pixmapItem->boundingRect();
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QString Card::color()
{
    return _color;
}

int Card::value()
{
    return _value;
}

int Card::stackNum() const
{
    return _stackNum;
}

void Card::setStackNum(int stackNum)
{
    _stackNum = stackNum;
}

int Card::rowNum() const
{
    return _rowNum;
}

void Card::setRowNum(int rowNum)
{
    _rowNum = rowNum;
}

void Card::setItemIsMovable(bool isMovable)
{
    _pixmapItem->setFlag(QGraphicsPixmapItem::ItemIsMovable, isMovable);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << _color << _value << "stack:" << _stackNum << "row:" << _rowNum;


//    if (clickedCard) {
//        // Tutaj możesz używać clickedCard jako obiektu typu Card
//        qDebug() << clickedCard->_color << clickedCard->_value;
//    }
//    qDebug() << "card event&&&&&&&&&&&&&&&&&";
//    QGraphicsItem* cardItem = scene()->itemAt(event->scenePos(), QTransform());
//    qDebug() << cardItem->data(0);
//    Card *card = dynamic_cast<Card*>(cardItem);
//    if(card != nullptr)
//    qDebug() << card->_color << _value;

//    QList<QGraphicsItem*> itemsAtPosition = scene()->items(event->scenePos());
//    for (QGraphicsItem* item : itemsAtPosition)
//    {
//        Card *cardItem = dynamic_cast<Card*>(item);
////        qDebug() << cardItem->color() << cardItem->value() << "stack:" << cardItem->stackNum() << "row:" << cardItem->rowNum();
//    }
    QGraphicsItem::mousePressEvent(event);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

int Card::type()
{
    return 65536;
}
