#include <QGraphicsSceneMouseEvent>

#include "abstractinstrument.h"
#include "pencilinstrument.h"
#include "geometricshapesinstrument.h"
#include "datasingleton.h"
#include "paintscene.h"

PaintScene::PaintScene(QWidget *parent)
    : QGraphicsScene(parent), modified(false) {

    DataSingleton::Instance().setInstrument(NONE_INSTRUMENT);

    setSceneRect(-200, -200, 400, 400);
    startSceneRect = sceneRect();

    instruments.fill(nullptr, static_cast<int>(INSTRUMENTS_COUNT));
    instruments[PEN] = new PencilInstrument(this);
    instruments[LINE] = new GeometricShapesInstrument(this, GeometricShapesInstrument::Line);
    instruments[RECTANGLE] = new GeometricShapesInstrument(this, GeometricShapesInstrument::Rectangle);
    instruments[ELLIPSE] = new GeometricShapesInstrument(this, GeometricShapesInstrument::Ellipse);
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    InstrumentsEnum tool = DataSingleton::Instance().instrument();
    if(tool != NONE_INSTRUMENT) {
        instrument = instruments.at(tool);
        instrument->mousePressEvent(e, *this);
        modified = true;
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseMoveEvent(e);
    InstrumentsEnum tool = DataSingleton::Instance().instrument();
    if(tool != NONE_INSTRUMENT) {
        instrument->mouseMoveEvent(e, *this);
        modified = true;
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e) {
    QGraphicsScene::mouseReleaseEvent(e);
    InstrumentsEnum tool = DataSingleton::Instance().instrument();
    if(tool != NONE_INSTRUMENT) {
        instrument->mouseMoveEvent(e, *this);
        modified = true;
    }
}

void PaintScene::clearImage() {
    qDeleteAll(items());
    modified = true;
    update();
}

bool PaintScene::openImage(const QString &fileName) {
    clearImage();
    if (!image.load(fileName))
        return false;
    addPixmap(image);
    setSceneRect(image.rect());
    return true;
}

bool PaintScene::saveImage(const QString &fileName, const char *fileFormat) {
    setSceneRect(itemsBoundingRect());
    QSize size = sceneRect().size().toSize();
    if (!size.width() || !size.height()) {
        size.setWidth(startSceneRect.width());
        size.setHeight(startSceneRect.height());
    }

    QImage image(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    render(&painter);

    setSceneRect(startSceneRect);
    if (image.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}
