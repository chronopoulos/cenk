#include "KickWidget.h"

KickWidget::KickWidget(void) : QFrame() {

    layout = new QVBoxLayout();

    nameLabel = new QLabel("kick");

    volSlider = new QSlider(Qt::Vertical);
    volSlider->setFocusPolicy(Qt::NoFocus);

    layout->addWidget(nameLabel);
    layout->addWidget(volSlider);

    this->setLayout(layout);

}
