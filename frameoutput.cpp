#include "frameoutput.h"
#include "ui_frameoutput.h"
#include <QMessageBox>
#include <QDebug>

FrameOutput::FrameOutput(QWidget *parent) : QFrame(parent),
    ui(new Ui::FrameOutput)
{
    ui->setupUi(this);



}

FrameOutput::~FrameOutput()
{
    delete ui;
}



void FrameOutput::setOutputText()
{

    qDebug()<< " output = "<<headingGyro;
    ui->outputTextEdit->insertPlainText("sdfdsf");

}

