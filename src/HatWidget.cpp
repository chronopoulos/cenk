#include "HatWidget.h"

HatWidget::HatWidget(HatSynth *hatSynth) : QFrame() {

    synth = hatSynth;

    layout = new QVBoxLayout();

    nameLabel = new QLabel("hat");

    volSlider = new QSlider(Qt::Vertical);
    volSlider->setFocusPolicy(Qt::NoFocus);

    layout->addWidget(nameLabel);
    layout->addWidget(volSlider);

    this->setLayout(layout);

    connect(volSlider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));

}

void HatWidget::setVolume(int volume) {

    synth->setVolume(volume / 99.);

}

