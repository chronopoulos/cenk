#ifndef KICKWIDGET_H
#define KICKWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>

class KickWidget : public QFrame {

    Q_OBJECT

    public:
        KickWidget(void);

    private:
        QVBoxLayout *layout;
        QLabel *nameLabel;
        QSlider *volSlider;

};

#endif
