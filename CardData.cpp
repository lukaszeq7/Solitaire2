#include "CardData.h"

CardData::CardData(const QString &color, int value) :
    _color(color),
    _value(value)
{

}

QString CardData::color() const
{
    return _color;
}

int CardData::value() const
{
    return _value;
}

int CardData::stackNum() const
{
    return _stackNum;
}

void CardData::setStackNum(int stackNum)
{
    _stackNum = stackNum;
}

int CardData::rowNum() const
{
    return _rowNum;
}

void CardData::setRowNum(int rowNum)
{
    _rowNum = rowNum;
}
