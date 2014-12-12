#include "lineinstrument.h"

LineInstrument::LineInstrument(QObject *parent)
    : AbstractInstrument(parent) {
}

void LineInstrument::mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &/*scene*/) {
    if(e->button() == Qt::LeftButton) {
        item = nullptr;
        startPoint = e->scenePos();
    }
}

void LineInstrument::mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    if (e->button() == Qt::LeftButton) {
        endPoint = e->scenePos();
        draw(scene);
    }
}

void LineInstrument::mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    if (item)
        scene.removeItem(item);
    endPoint = e->scenePos();
    draw(scene);
}

void LineInstrument::draw(PaintScene &scene) {
    QPen pen(DataSingleton::Instance().penColor(),
             DataSingleton::Instance().penWidth(),
             Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    item = scene.addLine(QLineF(startPoint, endPoint), pen);
    scene.update();
}
