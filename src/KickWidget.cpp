#include <QDebug>

#include "KickWidget.h"

KickWidget::KickWidget(KickSynth *kickSynth) : QFrame() {

    synth = kickSynth;

    layout = new QVBoxLayout();

    nameLabel = new QLabel("kick");

    volSlider = new QSlider(Qt::Vertical);
    volSlider->setFocusPolicy(Qt::NoFocus);

    layout->addWidget(nameLabel);
    layout->addWidget(volSlider);

    this->setLayout(layout);

    connect(volSlider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));

}

void KickWidget::setVolume(int volume) {

    synth->setVolume(volume / 99.);

}

