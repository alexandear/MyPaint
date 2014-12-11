#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>

#include "mainwindow.h"
#include "paintscene.h"
#include "instruments.h"


MainWindow::MainWindow() {
    instruments = new Instruments;
    paintScene = new PaintScene;
    view = new QGraphicsView(paintScene);

    QObject::connect(instruments, SIGNAL(toolChanged(int)),
                     paintScene, SLOT(setMode(int)));

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(instruments);
    hBoxLayout->addWidget(view);

    centralWidget = new QWidget;
    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);

}
