#ifndef SERIALPORTCONNECTOR_H
#define SERIALPORTCONNECTOR_H

#include <QObject>

#include "qextserialport.h"

class SerialPortConnector : public QObject
{
    Q_OBJECT

private:
    QextSerialPort *serialPort;

public:
    explicit SerialPortConnector(QObject *parent = 0);
    void setPortName(QString portName);
    void setBaudRate(BaudRateType baudRate);
    void setStopBits(StopBitsType stopBits);
    void setDataBits(DataBitsType dataBits);
    void setParity(ParityType parity);
    bool isOpen();
    void close();
    void open();
    void sendMessage( QString message );

signals:

public slots:
};

#endif // SERIALPORTCONNECTOR_H
