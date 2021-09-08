#include "dialogconfig.h"
#include "ui_dialogconfig.h"
#include "qextserialenumerator.h"
#include <QDebug>
#include "mainwindow.h"
#include "string"
#include <QMessageBox>
#include <unistd.h>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{


    ui->setupUi(this);



;

    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portNameCombo->addItem(info.portName);

    ui->baudRateCombo->addItem("1200");
    ui->baudRateCombo->addItem("2400");
    ui->baudRateCombo->addItem("4800");
    ui->baudRateCombo->addItem("9600");
    ui->baudRateCombo->addItem("19200");
    ui->baudRateCombo->addItem("38400");
    ui->baudRateCombo->addItem("115200");
    ui->baudRateCombo->setCurrentIndex(3);

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

    //=== configurasi serial port ===//
    connect(ui->portNameCombo, SIGNAL(editTextChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->baudRateCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onBaudRateChanged(QString)));
    connect(ui->stopBitsCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onStopBitsChanged(QString)));
    connect(ui->dataBitsCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onDataBitsChanged(QString)));
    connect(ui->parityCombo, SIGNAL(currentIndexChanged(QString)), SLOT(onParityChanged(QString)));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}

void DialogConfig::onPortNameChanged(const QString &/*name*/)
{
    portName = ui->portNameCombo->currentText();
}

void DialogConfig::onBaudRateChanged(const QString)
{
    baud = ui->baudRateCombo->currentText();
}

void DialogConfig::onStopBitsChanged(const QString)
{
    stopBit = ui->stopBitsCombo->currentText();
}

void DialogConfig::onDataBitsChanged(const QString)
{
    dataBit = ui->dataBitsCombo->currentText();
}

void DialogConfig::onParityChanged(const QString)
{
    paRity = ui->parityCombo->currentText();
}

void DialogConfig::on_buttonBoxSaveTCPConfig_accepted()
{
    socket = NULL;
    qDebug() << "connecting...";

    QString IP = ui->TcpEdit->text();
    QString port = ui->PortEdit->text();
    server = new (QTcpServer);
    if(server->listen(QHostAddress(IP),port.toInt()))
    {
        isconnectedTcp = true;
        qDebug()<<QDateTime::currentDateTime().toString()<<" tcp server is listening. IP "<<server->serverAddress().toString()<<" port "<<server->serverPort();
    }
    else
    {
        isconnectedTcp = false;
        QMessageBox::information(this,tr("FCS Simulator"),tr(server->errorString().toLatin1()));
        qDebug()<<QDateTime::currentDateTime().toString()<<" error when trying to configure tcp server. Error "<<server->errorString();
    }
    DialogConfig::close();
}

void DialogConfig::on_buttonBoxSaveConfig_accepted()
{
    serial.close();
    isconnected = false;
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
    serial.setParity(str2parity(paRity));
    serial.setStopBits(str2StopBit(stopBit));

    if (!serial.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,tr("FCS Simulator"),tr(portName.toLatin1()+" "+serial.errorString().toLatin1()));
        qDebug()<<serial.errorString()<<"nama portname "<<serial.portName()<<"baudRate "<<serial.baudRate()<<"Databits " <<serial.dataBits()<<"FlowControl "<<serial.flowControl()<<"Parity "<<serial.parity()<<"StopBits"<<serial.stopBits();
        isconnected = false;
    }
    else {
        isconnected = true;
    }
    DialogConfig::close();
}

//=== Serial ===//
void DialogConfig::SerialWrite(QString data)
{
        serial.write(data.toLatin1());
}

//=== Tcp ===//
void DialogConfig::TcpWrite(QString data)
{
    qDebug()<<Q_FUNC_INFO<<"connected";
    server->waitForNewConnection();
    if(server->hasPendingConnections())
    {
        if(socket)
            delete socket;
//        new SockClient( server->nextPendingConnection() )
        //socket = server.nextPendingConnection();
        socket = server->nextPendingConnection();
        qDebug()<<QDateTime::currentDateTime().toString()<<" new connection from ip "<<socket->peerAddress().toString()<<" socket descriptor "<<socket->socketDescriptor();
    }
    if(socket)
    {
        if (socket->state() == QAbstractSocket::ConnectedState)
        {
            socket->write(data.toUtf8());
            socket->waitForBytesWritten(1000);
            qDebug()<<Q_FUNC_INFO<< data;
        }
    }
}

void DialogConfig::disconnected()
{
    qDebug() << "disconnected...";
    serial.close();
}

void DialogConfig::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void DialogConfig::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}

QSerialPort::BaudRate DialogConfig::str2Baud(QString baud)
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

QSerialPort::DataBits DialogConfig::str2DataBit(QString databit)
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

QSerialPort::FlowControl DialogConfig::str2flwCtrl(QString flwCtrl)
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

QSerialPort::Parity DialogConfig::str2parity(QString parity)
{
    if (parity == "0" || parity == "NONE")
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

QSerialPort::StopBits DialogConfig::str2StopBit(QString stopBit)
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
