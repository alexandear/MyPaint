#ifndef INSTRUMENTSWIDGET_H
#define INSTRUMENTSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QButtonGroup;
class QPushButton;
QT_END_NAMESPACE

/*!
 * \brief Class that represents control elements of instruments.
 */
class InstrumentsWidget : public QWidget {

    Q_OBJECT

public:
    explicit InstrumentsWidget(QWidget *parent = nullptr);

private slots:
    void buttonGroupClicked(int id);
    void colorChosen();
    void penWidthChanged(int penWidth);

signals:

private:
    void changeButtonColor(QPushButton *button, const QColor &color);

    QButtonGroup *buttonGroup;
    QPushButton *cursorButton;
    QPushButton *penButton;
    QPushButton *lineButton;
    QPushButton *rectangleButton;
    QPushButton *ellipseButton;
    QVector<QPushButton *> buttons;
    QPushButton *penColorButton;
    QSpinBox *penWidthSpinBox;
};

#endif // INSTRUMENTSWIDGET_H
