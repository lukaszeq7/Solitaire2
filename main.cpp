#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/h1.png");

    QGraphicsView view;
    QGraphicsScene scene;

    QGraphicsPixmapItem item(pixmap);
    item.setFlag(QGraphicsItem::ItemIsMovable);
    scene.addItem(&item);

    view.setFixedSize(800, 600);
    view.setScene(&scene);
    view.show();

    return QApplication::exec();
}
