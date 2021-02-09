#include <QDebug>

#include "SerialPortConnector.h"

SerialPortConnector::SerialPortConnector(QObject *parent) : QObject(parent)
{
    serialPort = new QextSerialPort;

    serialPort->setBaudRate( BAUD38400 );
    serialPort->setStopBits( STOP_1 );
    serialPort->setDataBits( DATA_8 );
    serialPort->setParity( PAR_NONE );
}

void SerialPortConnector::setPortName(QString portName)
{
    serialPort->setPortName( portName );
}

void SerialPortConnector::setBaudRate(BaudRateType baudRate)
{
    serialPort->setBaudRate( baudRate );
}

void SerialPortConnector::setStopBits(StopBitsType stopBits)
{
    serialPort->setStopBits( stopBits );
}

void SerialPortConnector::setDataBits(DataBitsType dataBits)
{
    serialPort->setDataBits( dataBits );
}

void SerialPortConnector::setParity(ParityType parity)
{
    serialPort->setParity( parity );
}

bool SerialPortConnector::isOpen()
{
    return serialPort->isOpen();
}

void SerialPortConnector::close()
{
    if( isOpen() )
        serialPort->close();
}

void SerialPortConnector::open()
{
    if( !isOpen() )
        serialPort->open( QIODevice::WriteOnly );
}

void SerialPortConnector::sendMessage(QString message)
{
    if( isOpen() )
    {
        serialPort->write( message.toLatin1() );
//        qDebug() << "send" << message;
    }
    else
    {
        return;
    }
}

