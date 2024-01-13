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

private:
    Card* _card;

    void createAndAddCard();
};

#endif // SOLITAIRE2_BOARD_H
