#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mastertimer.start(1000);
}

void MainWindow::on_timeout()
{
//    ui->frameOutput->setHeading(ui->frameOutput->getHeading());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton clickedButton;
    clickedButton = QMessageBox::question( this, "Shutdown", "Shutdown System?",
                                           QMessageBox::Yes|QMessageBox::No );

    if( clickedButton != QMessageBox::Yes )
        return;
    close();
}
