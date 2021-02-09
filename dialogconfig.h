#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H
#include <QDialog>
#include <QSerialPort>
#include "SerialPortConnector.h"
#include "QTimer"
#include <QMap>
#include <QDebug>

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QDateTime>

#include <sstream>
#include <string.h>
#include <stdio.h>
#include <QStringList>

namespace Ui {
class DialogConfig;
}

class DialogConfig : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfig(QWidget *parent = nullptr);
    QString GetPortname(){return portName;}
    QString GetBaud(){return baud;}
    QString GetDatabit(){return dataBit;}
    QString GetParity(){return paRity;}
    QString GetStopBit(){return stopBit;}

    bool serialconnected(){return isconnected;}
    bool tcpconnected(){return  isconnectedTcp;}
    ~DialogConfig();

private:
    Ui::DialogConfig *ui;
    QTimer *sendTimer;
    QString portName;
    QString baud;
    QString dataBit;
    QString flowCtrl;
    QString paRity;
    QString stopBit;
    bool isconnected;
    bool isconnectedTcp;

    QSerialPort serial;

    QSerialPort::BaudRate str2Baud (QString baud);
    QSerialPort::DataBits str2DataBit (QString databit);
    QSerialPort::FlowControl str2flwCtrl (QString flwCtrl);
    QSerialPort::Parity str2parity (QString parity);
    QSerialPort::StopBits str2StopBit (QString stopBit);

    QTcpSocket *socket;
    QTcpServer *server;
    QTimer time;

public slots:
    void onPortNameChanged(const QString &);
    void onBaudRateChanged(const QString);
    void onStopBitsChanged(const QString);
    void onDataBitsChanged(const QString);
    void onParityChanged(const QString);

    void SerialWrite(QString data);
    void TcpWrite(QString data);

    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private slots:
    void on_buttonBoxSaveConfig_accepted();
    void on_buttonBoxSaveTCPConfig_accepted();
};

#endif // DIALOGCONFIG_H
