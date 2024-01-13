#include "CardData.h"

CardData::CardData(const QString &color, int value)
{

}

QString CardData::color() const
{
    return _color;
}

void CardData::setColor(const QString &color)
{
    _color = color;
}

int CardData::value() const
{
    return _value;
}

void CardData::setValue(int value)
{
    _value = value;
}
