#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

class AbstractInstrument;

class PaintScene : public QGraphicsScene {

    Q_OBJECT

public:
    PaintScene(QWidget *parent = nullptr);

    bool isModified() const { return modified; }
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);

public slots:
    void clearImage();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e);

private:
    bool modified;
    AbstractInstrument *instrument;
    QVector<AbstractInstrument *> instruments;
    QPixmap image;
    QRectF startSceneRect;

};

#endif // PAINTSCENE_H
