#include "mainwindow.h"
#include <QApplication>
#include "linedrawer.h"
#include <QLayout>
#include <QLabel>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QLabel wnd;
    MainWindow *pWindow = new MainWindow;

    //LineDrawer *wnd = new LineDrawer(50);
    //QVBoxLayout* pvbx = new QVBoxLayout;
    //pvbx->addWidget(pWindow);
    //pvbx->addWidget(w);
    //wnd.setLayout(pvbx);
    pWindow->show();

    //wnd->show();
    return a.exec();
}
