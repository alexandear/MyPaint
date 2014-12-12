#ifndef DATASINGLETON_H
#define DATASINGLETON_H

#include <QColor>

#include "instrumentsenum.h"

/*!
 * \brief The Data Singleton class
 *
 * This is sigleton for variables and settings of program.
 *
 */
class DataSingleton {

public:
    static DataSingleton& Instance() {
        static DataSingleton instance;
        return instance;
    }

    QColor penColor() const { return myPenColor; }
    void setPenColor(const QColor &penColor) { myPenColor = penColor; }
    int penWidth() const { return myPenWidth; }
    void setPenWidth(int penWidth) { myPenWidth = penWidth; }
    InstrumentsEnum instrument() const { return myInstrument; }
    void setInstrument(InstrumentsEnum instrument) { myInstrument = instrument; }
    QString getAppName() const { return QString("MyPaint"); }

    DataSingleton(DataSingleton const&) = delete;
    void operator=(const DataSingleton&) = delete;
private:
    DataSingleton();

    QColor myPenColor;
    int myPenWidth;
    InstrumentsEnum myInstrument;
};

#endif // DATASINGLETON_H
