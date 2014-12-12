#include "pencilinstrument.h"
#include "datasingleton.h"

PencilInstrument::PencilInstrument(QObject *parent) : AbstractInstrument(parent) {
}

void PencilInstrument::mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &/*scene*/) {
    if(e->button() == Qt::LeftButton) {
        startPoint = endPoint = e->scenePos();
    }
}

void PencilInstrument::mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    if (e->button() == Qt::LeftButton) {
        endPoint = e->scenePos();
        draw(scene);
    }
}

void PencilInstrument::mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    endPoint = e->scenePos();
    draw(scene);
}

void PencilInstrument::draw(PaintScene &scene) {
    QPen pen(DataSingleton::Instance().penColor(),
             DataSingleton::Instance().penWidth(),
             Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    scene.addLine(QLineF(startPoint, endPoint), pen);
    startPoint = endPoint;
    scene.update();
}
