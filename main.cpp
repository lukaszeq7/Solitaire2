#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include "MainWindow.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.setGeometry(
            QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    mainWindow.size(),
                    qApp->desktop()->availableGeometry()
            )
    );

    return QApplication::exec();
}
