#ifndef GEOMETRICSHAPESINSTRUMENT_H
#define GEOMETRICSHAPESINSTRUMENT_H

#include "abstractinstrument.h"
#include "paintscene.h"
#include "QGraphicsItem"

/*!
 * \brief Class that paints line, rectangle and ellipse.
 *
 */
class GeometricShapesInstrument : public AbstractInstrument {

public:
    enum Shape { Line = 0, Rectangle, Ellipse };
    explicit GeometricShapesInstrument(QObject *parent = nullptr, Shape shape = Rectangle);

    void mousePressEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e, PaintScene &scene);

    Shape shape() { return myShape; }
    void setShape(Shape shape) { myShape = shape; }

protected:
    void draw(PaintScene &scene);

private:
    Shape myShape;
    /*!
     * \brief Last shape that draws.
     */
    QGraphicsItem *item;
};

#endif // GEOMETRICSHAPESINSTRUMENT_H
