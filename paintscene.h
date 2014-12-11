#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>

class QGraphicsItem;

class PaintScene : public QGraphicsScene {

    Q_OBJECT

public:
    enum Mode { Draw, DrawRect, DrawEllipse };

    PaintScene(QWidget *parent = nullptr);

    void setPenColor(const QColor &penColor);
    void setPenWidth(int penWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    Mode mode() { return myMode; }

public slots:
    void setMode(int mode) {
        myMode = static_cast<Mode>(mode);
    }

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e);


private:
    QGraphicsItem* draw(const QPointF &endPointF);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QImage image;
    QColor myPenColor;
    Mode myMode;

    QPointF lastPointF;
    QGraphicsItem *lastItem;
    QImage paintAreaCopy;

};

#endif // PAINTSCENE_H
