#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>

#include "Session.h"

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();

    private:
        Session *session;
        QHBoxLayout *layout;

};

#endif
