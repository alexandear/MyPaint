#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H

#include <QObject>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

#include "paintscene.h"

/*!
 * \brief The Abstract Instrument class
 */
class AbstractInstrument : public QObject {

    Q_OBJECT

public:
    explicit AbstractInstrument(QObject *parent = nullptr);
    virtual ~AbstractInstrument() { }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene) = 0;

protected:
    virtual void draw(PaintScene &scene) = 0;

    QPointF startPoint, endPoint;
};

#endif // ABSTRACTINSTRUMENT_H
