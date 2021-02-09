#ifndef GYRODIALOG_H
#define GYRODIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "SerialPortConnector.h"

namespace Ui {
class GyroDialog;
}

class GyroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GyroDialog(QWidget *parent = nullptr);
    SerialPortConnector *serialPortConnector;

    ~GyroDialog();

private:
    Ui::GyroDialog *ui;
    QTimer *sendTimer;
    QSerialPort serial;
    QString portName;
    QString baud;
    QString dataBit;
    QString flowCtrl;
    QString paRity;
    QString stopBit;


     QSerialPort::BaudRate str2Baud (QString baud);
     QSerialPort::DataBits str2DataBit (QString databit);
     QSerialPort::FlowControl str2flwCtrl (QString flwCtrl);
     QSerialPort::Parity str2parity (QString parity);
     QSerialPort::StopBits str2StopBit (QString stopBit);

public slots:
    void onPortNameChanged(const QString &);
    void onBaudRateChanged(const QString);
    void onStopBitsChanged(const QString);
    void onDataBitsChanged(const QString);
    void onParityChanged(const QString);
    void onTimer();



private slots:
    void on_pushButtonSaveSerialGyro_clicked();
};

#endif // GYRODIALOG_H
