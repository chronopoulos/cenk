#ifndef HATWIDGET_H
#define HATWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>

#include "HatSynth.h"

class HatWidget : public QFrame {

    Q_OBJECT

    public:

        HatWidget(HatSynth*);

    private:

        QVBoxLayout *layout;
        QLabel *nameLabel;
        QSlider *volSlider;

        HatSynth *synth;

    public slots:

        void setVolume(int);

};

#endif
