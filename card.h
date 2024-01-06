#ifndef SOLITAIRE2_CARD_H
#define SOLITAIRE2_CARD_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class Card : public QGraphicsObject
{
Q_OBJECT

public:
    explicit Card(QGraphicsItem* parent = nullptr);

    Card::~Card() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsPixmapItem* _pixmapItem;
};

#endif //SOLITAIRE2_CARD_H
