#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class PaintScene;
class QButtonGroup;
class QPushButton;
class Instruments;
class QGraphicsView;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();

    PaintScene *paintScene;
    Instruments *instruments;

    QWidget *centralWidget;

    QGraphicsView *view;

};

#endif // MAINWINDOW_H
