#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QButtonGroup;
class QPushButton;
class QGraphicsView;
QT_END_MOC_NAMESPACE

class PaintScene;
class InstrumentsWidget;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();

    PaintScene *paintScene;
    InstrumentsWidget *instruments;
    QWidget *centralWidget;
    QGraphicsView *view;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void open();
    void save();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    void setAppTitle(const QString &title);

    QMenu *fileMenu;
    QMenu *saveAsMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QList<QAction *> saveAsActs;
    QAction *openAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    QAction *aboutAct;

};

#endif // MAINWINDOW_H
