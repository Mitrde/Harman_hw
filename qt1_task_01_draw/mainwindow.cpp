#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "linedrawer.h"
#include "editdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(numChanged(size_t)),
            ui->lineDrawer,SLOT(numCh(size_t)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionInput_triggered()
{
    EditDialog *pdlg = new EditDialog(this);
    pdlg->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QString aboutMessage = "Нарисовать заданное количество точек, расположенных на окружности "
                               "некторого радиуса на равном расстоянии друг от друга. "
                               "Каждая точка должна быть соединена с каждой другой отрезком. "
                               "С внешней стороны окружности возле каждой точки необходимо"
                               " напечатать её порядковый номер. ";

        QMessageBox::about(this, tr("About the program"), aboutMessage);
}
