#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    QRect display = QApplication::desktop()->screenGeometry();
    window.setMinimumSize(display.width() / 2, display.height() / 2);
    window.show();
    return app.exec();
}
