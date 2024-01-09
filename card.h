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
    explicit Card(QString color, int value, QGraphicsItem* parent = nullptr);

    Card::~Card() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QString color();
    int value();

    QPointF position();
    void setPosition(QPointF position);

signals:
    void cardPressed(QList<Card*> cardsPressed);
    void cardReleased(QList<Card*> cardsReleased);

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

    QString _color;
    int _value;

    int _stackNumber;
    int _rowNumber;
    QPointF _position;
};

#endif //SOLITAIRE2_CARD_H
