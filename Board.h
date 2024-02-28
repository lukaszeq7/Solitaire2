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

    void initCards(int numberOfDecksDfCards);
    void spreadCards();

    QList<Card*> getCardsAtPosition(const QList<QGraphicsItem*>& itemsAtPosition);
    Card* clickedCard(const QList<QGraphicsItem*>& itemsAtPosition, int cardIndex);
    bool isSelectedCardsMoveable();
    bool isSelectedCardsPositionable(bool isReleaseOnFreeStack);
    QList<Card*> selectedCards(int stackNum, int rowNum);

    void addCardsToGroup(const QList<Card*>& selectedCards);

    void setCardsOnPositions(QList<Card*> selectedCards, int stackNum);
    void appendCardsToStack(const QList<Card*>& selectedCards, int stackNum);
    void removeCardsFromStack(const QList<Card*>& selectedCards, int stackNum);
    void updateCardsData(int stackNum);

    void showCardsData(const QList<Card*>& cardList, const QString& text);

    bool isCardsInOrder(Card* firstCard, Card* secondCard);
    bool isSameColor(Card* firstCard, Card* secondCard);

    void pickUpTheCards(QList<Card*>& selectedCards, int stackNum);
    void layDownTheCards(const QList<Card*>& selectedCards, int stackNum);

    void collectCardsIfInOrder(int stackNum);


    bool isCardsRemoveable(int stackNum);

    void collectCards(int stackNum);

    void setupBoard();
};

#endif // SOLITAIRE2_BOARD_H
