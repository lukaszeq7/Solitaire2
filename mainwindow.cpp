#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _board(new Board(this)),
        _view(new QGraphicsView(this))
{
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _view->setScene(_board);

    _sceneWidth = _view->scene()->width();
    _sceneHeight = 1000;
    _board->setSceneRect(0, 0, _sceneWidth, _sceneHeight);
    _view->setFixedSize(_sceneWidth, _sceneHeight);
    setFixedSize(_sceneWidth, _sceneHeight);
    
    _view->show();
}

MainWindow::~MainWindow()
{

}
