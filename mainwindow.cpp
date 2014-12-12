#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QImageWriter>
#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QFileInfo>

#include "mainwindow.h"
#include "paintscene.h"
#include "instrumentswidget.h"
#include "datasingleton.h"

MainWindow::MainWindow() {
    instruments = new InstrumentsWidget;
    paintScene = new PaintScene;

    view = new QGraphicsView(paintScene);
    //view->centerOn(0, 0);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(instruments);
    hBoxLayout->addWidget(view);

    centralWidget = new QWidget;
    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);

    createActions();
    createMenus();

    setAppTitle("untitled");
}

void MainWindow::open() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                       tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty()) {
            paintScene->openImage(fileName);
            setAppTitle(QFileInfo(fileName).fileName());
        }
    }
}

void MainWindow::save() {
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::closeEvent(QCloseEvent *e) {
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About MyPaint"),
            tr("<p><b>MyPaint</b> is simple painting application for "
               "drawing lines, rectangles and ellipses</p>"));
}

void MainWindow::createActions() {

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()), paintScene, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus() {

    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave() {
    if (paintScene->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("MyPaint"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat) {
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        setAppTitle(QFileInfo(fileName).fileName());
        return paintScene->saveImage(fileName, fileFormat.constData());
    }
}

void MainWindow::setAppTitle(const QString &title) {
    setWindowTitle(title + " - " + DataSingleton::Instance().getAppName());
}
