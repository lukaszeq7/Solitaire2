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

    int cardRowNum() const;
    void setCardRowNum(int cardRowNum);

    int cardStackNum() const;
    void setCardStackNum(int cardStackNum);

private:
    Card _card;
    CardData* _cardData;
    QList<Card*> _cards;
    QList<QList<Card*>> _stacks;

    void spreadCards();
};

#endif // SOLITAIRE2_BOARD_H
