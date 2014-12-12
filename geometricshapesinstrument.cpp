#include "geometricshapesinstrument.h"
#include "datasingleton.h"

GeometricShapesInstrument::GeometricShapesInstrument(QObject *parent, Shape figure)
    : AbstractInstrument(parent), myShape(figure), item(nullptr) {
}

void GeometricShapesInstrument::mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &/*scene*/) {
    if(e->button() == Qt::LeftButton) {
        item = nullptr;
        startPoint = e->scenePos();
    }
}

void GeometricShapesInstrument::mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    if (e->button() == Qt::LeftButton) {
        endPoint = e->scenePos();
        draw(scene);
    }
}

void GeometricShapesInstrument::mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) {
    if (item)
        scene.removeItem(item);
    endPoint = e->scenePos();
    draw(scene);
}

void GeometricShapesInstrument::draw(PaintScene &scene) {
    if (startPoint != endPoint) {
        QPen pen(DataSingleton::Instance().penColor(),
                 DataSingleton::Instance().penWidth(),
                 Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        QRectF rect(startPoint, endPoint);
        switch(myShape) {
        case Line:
            item = scene.addLine(QLineF(startPoint, endPoint), pen);
            break;
        case Rectangle:
            item = scene.addRect(rect, pen);
            break;
        case Ellipse:
            item = scene.addEllipse(rect, pen);
            break;
        }
        scene.update();
    }
}
