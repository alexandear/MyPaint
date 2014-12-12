#ifndef PENCILINSTRUMENT_H
#define PENCILINSTRUMENT_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "abstractinstrument.h"

class PencilInstrument : public AbstractInstrument {

public:
    explicit PencilInstrument(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);

protected:
    void draw(PaintScene &scene);
};

#endif // PENCILINSTRUMENT_H
