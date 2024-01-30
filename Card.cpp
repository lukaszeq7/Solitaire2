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
}

Card::Card(const QString &color, QGraphicsItem *parent) :
        QGraphicsItem(parent),
        _color(color),
        _pixmapItem(new QGraphicsPixmapItem(this))
{
    QString imagePath(":/images/" + _color + ".png");
    QPixmap pixmap(imagePath);
    _pixmapItem->setPixmap(pixmap);
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

int Card::type()
{
    return 65536;
}