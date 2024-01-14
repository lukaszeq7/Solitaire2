#ifndef CARDDATA_H
#define CARDDATA_H

#include <QString>

class CardData {
public:
    CardData(const QString& color, int value);

    QString color() const;
    int value() const;

    int stackNum() const;
    void setStackNum(int stackNum);

    int rowNum() const;
    void setRowNum(int rowNum);

private:
    QString _color;
    int _value;

    int _stackNum;
    int _rowNum;
};

#endif // CARDDATA_H
