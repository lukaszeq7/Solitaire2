#ifndef SOLITAIRE2_CARD_H
#define SOLITAIRE2_CARD_H

#include <QGraphicsItem>
#include <QPixmap>
#include "CardData.h"

class Card : public QGraphicsItem
{
public:
    explicit Card(QGraphicsItem *parent = nullptr);

    ~Card() override;

    virtual QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    CardData* _cardData;
    QGraphicsPixmapItem* _pixmapItem;
};

#endif //SOLITAIRE2_CARD_H
