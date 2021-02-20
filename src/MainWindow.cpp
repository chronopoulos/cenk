#include <QLabel>

#include "MainWindow.h"
#include "KickWidget.h"
#include "KickSynth.h"

MainWindow::MainWindow() : QWidget() {

    session = new Session();
    layout = new QHBoxLayout();

    KickSynth *kickSynth1 = new KickSynth(1);
    session->addSynth(kickSynth1);

    KickSynth *kickSynth2 = new KickSynth(2);
    session->addSynth(kickSynth2);

    //KickWidget *kickWidget = new KickWidget(kickSynth);

    layout->addWidget(new KickWidget());
    layout->addWidget(new KickWidget());
    layout->addWidget(new KickWidget());
    layout->addWidget(new KickWidget());

    this->setLayout(layout);
    this->setWindowTitle("trox");

    session->start();

}
