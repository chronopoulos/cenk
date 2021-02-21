#include <QLabel>

#include "MainWindow.h"
#include "KickWidget.h"
#include "KickSynth.h"
#include "HatSynth.h"

MainWindow::MainWindow() : QWidget() {

    session = new Session();
    layout = new QHBoxLayout();

    KickSynth *kickSynth = new KickSynth(1);
    session->addSynth(kickSynth);

    HatSynth *hatSynth = new HatSynth(2);
    session->addSynth(hatSynth);

    //KickWidget *kickWidget = new KickWidget(kickSynth);   // TODO

    layout->addWidget(new KickWidget());
    layout->addWidget(new KickWidget());

    this->setLayout(layout);
    this->setWindowTitle("trox");

    session->start();

}
