#ifndef SOLITAIRE2_MAINWINDOW_H
#define SOLITAIRE2_MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include "card.h"

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    MainWindow::~MainWindow() override;

public slots:
    void onCardPressed(Card* cardPressed);
    void onCardReleased(QList<Card*> cardsPressed);

private:
    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QList<Card*> _cards;
    QList<QList<Card*>> _stacks;
    QList<Card*> _selectedCards;
    QGraphicsItemGroup* _selectedCardsGroup;

    const int _vSpace;
    const int _hSpace;

    QList<Card*> stackItemsToCards(qreal x);
};

#endif //SOLITAIRE2_MAINWINDOW_H
