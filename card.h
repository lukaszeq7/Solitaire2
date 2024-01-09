#ifndef SOLITAIRE2_CARD_H
#define SOLITAIRE2_CARD_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsScene>

class Card : public QGraphicsObject
{
Q_OBJECT

public:
    explicit Card(QGraphicsItem* parent = nullptr);

    Card::~Card() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:
    void cardPressed(Card* cardPressed);
    void cardReleased(Card* cardReleased);

public slots:
    int stackNumber();
    void setStackNumber(int stackNumber);

    int rowNumber();
    void setRowNumber(int rowNumber);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsPixmapItem* _pixmapItem;
    int _stackNumber;
    int _rowNumber;
    QPointF position;
    bool isPressed;
};

#endif //SOLITAIRE2_CARD_H
