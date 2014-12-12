#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QFrame>
#include <QColorDialog>
#include <QSpinBox>

#include "instrumentswidget.h"
#include "datasingleton.h"
#include "instrumentsenum.h"

InstrumentsWidget::InstrumentsWidget(QWidget *parent) : QWidget(parent) {

    cursorButton = new QPushButton("Cursor");
    penButton = new QPushButton("Pen");
    lineButton = new QPushButton("Line");
    rectangleButton = new QPushButton("Rect");
    ellipseButton = new QPushButton("Ellipse");

    buttons.append(cursorButton);
    buttons.append(penButton);
    buttons.append(lineButton);
    buttons.append(rectangleButton);
    buttons.append(ellipseButton);

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(true);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));

    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i]->setCheckable(true);
        vBoxLayout->addWidget(buttons[i]);
        buttonGroup->addButton(buttons[i], i);
    }
    buttons[NONE_INSTRUMENT]->setChecked(true);

    QFrame* lineSep = new QFrame();
    lineSep->setFrameShape(QFrame::HLine);
    lineSep->setFrameShadow(QFrame::Sunken);
    vBoxLayout->addWidget(lineSep);

    penColorButton = new QPushButton;
    QColor oldColor = DataSingleton::Instance().penColor();
    changeButtonColor(penColorButton, oldColor);
    vBoxLayout->addWidget(penColorButton);
    connect(penColorButton, SIGNAL(clicked()), this, SLOT(colorChosen()));

    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(1, 99);
    vBoxLayout->addWidget(penWidthSpinBox);
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(penWidthChanged(int)));

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    vBoxLayout->addSpacerItem(spacer);
    setLayout(vBoxLayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void InstrumentsWidget::buttonGroupClicked(int id) {
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    DataSingleton::Instance().setInstrument(static_cast<InstrumentsEnum>(id));
}

void InstrumentsWidget::colorChosen() {
    QColor newColor = QColorDialog::getColor(DataSingleton::Instance().penColor());
    if (newColor.isValid()) {
        DataSingleton::Instance().setPenColor(newColor);
        changeButtonColor(penColorButton, newColor);
    }
}

void InstrumentsWidget::penWidthChanged(int penWidth) {
    DataSingleton::Instance().setPenWidth(penWidth);
}

void InstrumentsWidget::changeButtonColor(QPushButton *button, const QColor &color) {
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";");
    button->setStyleSheet(s);
    button->update();
}
