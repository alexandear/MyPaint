#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "paintscene.h"


PaintScene::PaintScene(QWidget *parent) : QGraphicsScene(parent) {

    lastItem = nullptr;
    setSceneRect(50, 50, 400, 400);

    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    myMode = Draw;
}

void PaintScene::setPenColor(const QColor &penColor) {
    this->myPenColor = penColor;
}

void PaintScene::setPenWidth(int penWidth) {
    this->myPenWidth = penWidth;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mousePressEvent(e);
    if (e->button() == Qt::LeftButton) {
        lastPointF = e->scenePos();
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseMoveEvent(e);
    if ((e->buttons() & Qt::LeftButton)) {
        if (lastItem && myMode != Draw)
            removeItem(lastItem);
        lastItem = draw(e->scenePos());
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseReleaseEvent(e);
    if (e->button() == Qt::LeftButton) {
        draw(e->scenePos());
    }
}

QGraphicsItem* PaintScene::draw(const QPointF &endPointF) {

    QGraphicsItem *item = nullptr;
    if (lastPointF != endPointF) {
        QPen pen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        switch (myMode) {
        case Draw:
            item = addLine(QLineF(lastPointF, endPointF), pen);
            lastPointF = endPointF;
            break;
        case DrawRect:
            item = addRect(QRectF(lastPointF, endPointF), pen);
            break;
        case DrawEllipse:
            item = addEllipse(QRectF(lastPointF, endPointF), pen);
            break;
        }
        modified = true;
    }
    return item;
}
