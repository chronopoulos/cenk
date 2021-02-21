#include <QLabel>

#include "MainWindow.h"

#include "KickSynth.h"
#include "HatSynth.h"

#include "KickWidget.h"
#include "HatWidget.h"

MainWindow::MainWindow() : QWidget() {

    session = new Session();
    layout = new QHBoxLayout();

    KickSynth *kickSynth = new KickSynth(1);
    session->addSynth(kickSynth);
    KickWidget *kickWidget = new KickWidget(kickSynth);
    layout->addWidget(kickWidget);

    HatSynth *hatSynth = new HatSynth(2);
    session->addSynth(hatSynth);
    HatWidget *hatWidget = new HatWidget(hatSynth);
    layout->addWidget(hatWidget);

    this->setLayout(layout);
    this->setWindowTitle("trox");

    session->start();

}
