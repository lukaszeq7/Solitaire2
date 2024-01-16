#ifndef SOLITAIRE2_CARD_H
#define SOLITAIRE2_CARD_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>

class Card : public QGraphicsItem
{
public:
    explicit Card(const QString& color, int value, QGraphicsItem *parent = nullptr);

    ~Card() override;

    virtual QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString color();
    int value();

    int stackNum() const;
    void setStackNum(int stackNum);

    int rowNum() const;
    void setRowNum(int rowNum);

    void setItemIsMovable(bool isMovable);

    int type();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString _color;
    int _value;
    QGraphicsPixmapItem* _pixmapItem;

    int _stackNum;
    int _rowNum;
};

#endif //SOLITAIRE2_CARD_H
