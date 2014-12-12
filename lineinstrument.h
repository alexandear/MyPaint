#ifndef LINEINSTRUMENT_H
#define LINEINSTRUMENT_H

#include <QGraphicsItem>

#include "abstractinstrument.h"
#include "datasingleton.h"

class LineInstrument : public AbstractInstrument {
public:
    explicit LineInstrument(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);

protected:
    void draw(PaintScene &scene);
private:
    QGraphicsItem *item;
};

#endif // LINEINSTRUMENT_H
