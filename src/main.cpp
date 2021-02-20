/*

    [trox]

    Chris Chronopoulos 20210213

*/

#include <QApplication>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    app.setApplicationName("trox");

    QFont font("Monospace");
    font.setBold(true);
    font.setPointSize(10);
    app.setFont(font);

    MainWindow mainWindow;
    if (app.arguments().length() > 1) {
        //mainWindow.load(app.arguments().at(1));
    }

    mainWindow.show();

    return app.exec();

}
