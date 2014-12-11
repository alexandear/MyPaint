#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>

#include <QDebug>

#include "instruments.h"


Instruments::Instruments(QWidget *parent) : QWidget(parent) {

    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(true);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));

    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    penButton = new QPushButton("Pen");
    rectangleButton = new QPushButton("Rect");
    ellipseButton = new QPushButton("Ellipse");

    penButton->setCheckable(true);
    rectangleButton->setCheckable(true);
    ellipseButton->setCheckable(true);

    vBoxLayout->addWidget(penButton);
    vBoxLayout->addWidget(rectangleButton);
    vBoxLayout->addWidget(ellipseButton);
    setLayout(vBoxLayout);

    buttonGroup->addButton(penButton, Pen);
    buttonGroup->addButton(rectangleButton, Rectangle);
    buttonGroup->addButton(ellipseButton, Ellipse);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void Instruments::buttonGroupClicked(int id) {
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    setTool(static_cast<Tool>(id));
}
