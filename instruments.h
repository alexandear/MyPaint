#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <QWidget>

class QButtonGroup;
class QPushButton;

class Instruments : public QWidget {

    Q_OBJECT

public:
    enum Tool { Pen = 0, Rectangle, Ellipse };

    Instruments(QWidget *parent = nullptr);

    Tool tool() const { return myTool; }
    void setTool(Tool tool) {
        myTool = tool;
        emit toolChanged(static_cast<int>(tool));
    }

private slots:
    void buttonGroupClicked(int id);

signals:
    void toolChanged(int tool);

private:
    QButtonGroup *buttonGroup;
    Tool myTool;

    QPushButton *penButton;
    QPushButton *rectangleButton;
    QPushButton *ellipseButton;
};

#endif // INSTRUMENTS_H
