#include "gyrodialog.h"
#include "ui_gyrodialog.h"
#include "qextserialenumerator.h"
#include <QDebug>
#include "mainwindow.h"


GyroDialog::GyroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GyroDialog)
{
    ui->setupUi(this);

    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portNameCombo->addItem(info.portName);

    ui->baudRateCombo->addItem("1200");
    ui->baudRateCombo->addItem("2400");
    ui->baudRateCombo->addItem("4800");
    ui->baudRateCombo->addItem("9600");
    ui->baudRateCombo->addItem("19200");
    ui->baudRateCombo->addItem("38400");
    ui->baudRateCombo->addItem("115200");
    ui->baudRateCombo->setCurrentIndex(5);

    ui->stopBitsCombo->addItem("1");
    ui->stopBitsCombo->addItem("2");

    ui->dataBitsCombo->addItem("5");
    ui->dataBitsCombo->addItem("6");
    ui->dataBitsCombo->addItem("7");
    ui->dataBitsCombo->addItem("8");
    ui->dataBitsCombo->setCurrentIndex(3);

    ui->parityCombo->addItem("NONE");
    ui->parityCombo->addItem("ODD");
    ui->parityCombo->addItem("EVEN");


    //== configurasi serial port

    connect(ui->portNameCombo, SIGNAL(editTextChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->baudRateCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onBaudRateChanged(QString)));
    connect(ui->stopBitsCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onStopBitsChanged(QString)));
    connect(ui->dataBitsCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onDataBitsChanged(QString)));
    connect(ui->parityCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onParityChanged(QString)));


}

GyroDialog::~GyroDialog()
{
    delete ui;
}



void GyroDialog::onPortNameChanged(const QString &/*name*/)
{

portName = ui->portNameCombo->currentText();
   // serialPortConnector->isOpen();
    //ui->openCloseLed->turnOff();
   // ui->statusbar->showMessage( "Serial Port closed" );

}

void GyroDialog::onBaudRateChanged(const QString)
{
      baud = ui->baudRateCombo->currentText();
}

void GyroDialog::onStopBitsChanged(const QString)
{
       stopBit = ui->stopBitsCombo->currentText();
}

void GyroDialog::onDataBitsChanged(const QString)
{
    dataBit = ui->dataBitsCombo->currentText();
}

void GyroDialog::onParityChanged(const QString)
{
    paRity = ui->parityCombo->currentText();
}

void GyroDialog::on_pushButtonSaveSerialGyro_clicked()
{
     portName = ui->portNameCombo->currentText();
     baud = ui->baudRateCombo->currentText();
     stopBit = ui->stopBitsCombo->currentText();
     dataBit = ui->dataBitsCombo->currentText();
     paRity = ui->parityCombo->currentText();



     qDebug()<< "Portname = " << portName << endl;
     qDebug()<< "baud = " << baud << endl;
     qDebug()<< "stopbits = " << stopBit << endl;
     qDebug()<< "databit = " << dataBit << endl;
     qDebug()<< "onparity = " << paRity << endl;

       serial.setPortName(portName);
       serial.setBaudRate(str2Baud(baud));
       serial.setDataBits(str2DataBit(dataBit));
       serial.setFlowControl(str2flwCtrl(flowCtrl));
       serial.setParity(str2parity(paRity));
       serial.setStopBits(str2StopBit(stopBit));
       if (!serial.open(QIODevice::ReadWrite))
               {
                   qDebug()<< "not connected";
                   qDebug()<<serial.errorString()<<"nama portname "<<serial.portName()<<"baudRate "<<serial.baudRate()<<"Databits " <<serial.dataBits()<<"FlowControl "<<serial.flowControl()<<"Parity "<<serial.parity()<<"StopBits"<<serial.stopBits();
                   GyroDialog::close();
               }
       sendTimer = new QTimer( this );
          int sendInterval = 100; // milliseconds
          sendTimer->setInterval( sendInterval );

       connect(sendTimer, SIGNAL(timeout()),this, SLOT(onTimer()));

       GyroDialog::close();




     //  QString data_send = nmeaData.mid(nmeaDataIndx,num);
      //        qDebug()<<Q_FUNC_INFO<<"send data"<<data_send;




//MainWindow().tes();



//        if( !serialPortConnector->isOpen() )
//        {
//            serialPortConnector->setPortName( ui->portNameCombo->currentText() );
//            serialPortConnector->open();
//           // ui->statusbar->showMessage( "Serial Port opened" );

//        }
//        else
//        {

//            serialPortConnector->close();
          //  sendTimer->stop();
           // ui->pushButtonGyroStart->setText( "Start Sending!!" );
          //  ui->statusbar->showMessage( "Serial Port closed!!!" );

       // }

       // ui->openCloseLed->turnOn( serialPortConnector->isOpen() );
         qDebug()<<"connected";

}

void GyroDialog::onTimer()
{
qDebug()<<"tes";
}


QSerialPort::BaudRate GyroDialog::str2Baud(QString baud)
{
    if (baud == "4800")
        return QSerialPort::Baud4800;
    else if (baud == "9600")
        return QSerialPort::Baud9600;
    else if (baud =="19200")
        return QSerialPort::Baud19200;
    else if (baud == "38400")
        return QSerialPort::Baud38400;
    else if (baud == "57600")
        return QSerialPort::Baud57600;
    else if(baud == "115200")
        return QSerialPort::Baud115200;
    else
        return QSerialPort::UnknownBaud; //invalid
}

QSerialPort::DataBits GyroDialog::str2DataBit(QString databit)
{
    if (databit == "8")
        return QSerialPort::Data8;
    else if (databit == "7")
        return QSerialPort::Data7;
    else if (databit == "6")
        return QSerialPort::Data6;
    else if(databit == "5")
        return QSerialPort::Data5;
    else
        return QSerialPort::UnknownDataBits; //invalid

}

QSerialPort::FlowControl GyroDialog::str2flwCtrl(QString flwCtrl)
{
    if (flwCtrl == "No")
        return QSerialPort::NoFlowControl;
    else if (flwCtrl == "HW")
        return QSerialPort::HardwareControl;
    else if (flwCtrl == "SW")
        return QSerialPort::SoftwareControl;
    else
        return QSerialPort::UnknownFlowControl; //invalid
}

QSerialPort::Parity GyroDialog::str2parity(QString parity)
{
    if (parity == "0")
        return QSerialPort::NoParity;
    else if (parity == "2")
        return QSerialPort::EvenParity;
    else if (parity == "3")
        return QSerialPort::OddParity;
    else if (parity == "4")
        return QSerialPort::SpaceParity;
    else if (parity == "5")
        return QSerialPort::MarkParity;
    else
        return QSerialPort::UnknownParity; //invalid
}

QSerialPort::StopBits GyroDialog::str2StopBit(QString stopBit)
{
    if (stopBit == "1")
        return QSerialPort::OneStop;
    else if (stopBit == "3")
        return QSerialPort::OneAndHalfStop;
    else if (stopBit == "2")
        return QSerialPort::TwoStop;
    else
        return QSerialPort::UnknownStopBits; //invalid
}

