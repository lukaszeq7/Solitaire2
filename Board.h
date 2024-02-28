#ifndef SOLITAIRE2_BOARD_H
#define SOLITAIRE2_BOARD_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
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
    const int _numberOfDecksOfCards;
    const int _numberOfFullCardsPerColor;
    Card* _sampleCard;

    QList<Card*> _freeStackCards;
    QList<Card*> _cards;
    QList<QList<Card*>> _stacks;

    int _hSpace;
    int _vSpace;
    int _srcCardStackNum;
    int _srcCardRowNum;
    int _destCardStackNum;

    QList<Card*> _selectedCards;
    QGraphicsItemGroup* _cardGroup;

    void setupBoard();
    void initCards(int numberOfDecksDfCards);
    void spreadCards();
    void shuffleCards();

    QList<Card*> cardsAtPosition(const QList<QGraphicsItem*>& itemsAtPosition);
    QList<Card*> selectedCards(int stackNum, int rowNum);
    bool isSelectedCardsPositionable(bool isReleaseOnFreeStack);

    void pickUpTheCards(QList<Card*>& selectedCards, int stackNum);
    bool isSelectedCardsMoveable();
    void updateCardsData(int stackNum);
    void addCardsToGroup(const QList<Card*>& selectedCards);
    void removeCardsFromStack(const QList<Card*>& selectedCards, int stackNum);

    void layDownTheCards(const QList<Card*>& selectedCards, int stackNum);
    void setCardsOnPositions(QList<Card*> selectedCards, int stackNum);
    void appendCardsToStack(const QList<Card*>& selectedCards, int stackNum);

    void collectCardsIfInOrder(int stackNum);
    bool isCardsRemoveable(int stackNum);
    void collectCards(int stackNum);

    bool isCardsInOrder(Card* firstCard, Card* secondCard);
    bool isSameColor(Card* firstCard, Card* secondCard);

    void showCardsData(const QList<Card*>& cardList, const QString& text);
};

#endif // SOLITAIRE2_BOARD_H
