#ifndef SOLITAIRE2_BOARD_H
#define SOLITAIRE2_BOARD_H

#include <QGraphicsScene>
#include <QWidget>
#include <QDebug>
#include "Card.h"

class Board : public QGraphicsScene
{
Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board() override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Card* _sampleCard;

    QList<Card*> _cards;
    QList<QList<Card*>> _stacks;

    int _hSpace;
    int _vSpace;

    void spreadCards();
};

#endif // SOLITAIRE2_BOARD_H
