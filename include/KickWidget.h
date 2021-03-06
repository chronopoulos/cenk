#ifndef KICKWIDGET_H
#define KICKWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>

#include "KickSynth.h"

class KickWidget : public QFrame {

    Q_OBJECT

    public:

        KickWidget(KickSynth*);

    private:

        QVBoxLayout *layout;
        QLabel *nameLabel;
        QSlider *volSlider;

        KickSynth *synth;

    public slots:

        void setVolume(int);

};

#endif
