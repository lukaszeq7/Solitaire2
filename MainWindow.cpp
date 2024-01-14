#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent),
        _board(new Board(this)),
        _view(new QGraphicsView(this))
{
    _view->setFixedSize(800, 600);
    _view->setScene(_board);
    _view->show();
}

MainWindow::~MainWindow()
{

}
