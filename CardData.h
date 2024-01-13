#ifndef CARDDATA_H
#define CARDDATA_H

#include <QString>

class CardData {
public:
    CardData(const QString& color, int value);

    QString color() const;
    void setColor(const QString& color);

    int value() const;
    void setValue(int value);

private:
    QString _color;
    int _value;
};

#endif // CARDDATA_H
