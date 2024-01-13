#include "Board.h"

Board::Board(QWidget *parent)
        : QGraphicsScene(parent)
{
    createAndAddCard();
}

Board::~Board()
{

}

void Board::createAndAddCard()
{
    _card = new Card();
    _card->setPos(100, 100);
    addItem(_card);
}
