#ifndef FRAMEOSDSET_H
#define FRAMEOSDSET_H
#include "dialogconfig.h"
#include <QFrame>
#include <QWidget>
#include <QSerialPort>
#include <QTcpServer>
#include <QTimer>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QDateTime>
#include <nmeagenerator.h>

namespace Ui {
class FrameOSDSet;
}

class FrameOSDSet : public QFrame
{
    Q_OBJECT

public:
    explicit FrameOSDSet(QWidget *parent = nullptr);

    ~FrameOSDSet();

public slots:
    void on_GyroTimer();
    void on_GpsTimer();
    void on_SpeedTimer();
    void on_WaterTimer();
    void on_WindTimer();
    void on_WeatherTimer();

private slots:
    void on_pushButtonGyroSetting_clicked();
    void on_pushButtonGyroApply_clicked();
    void on_pushButtonGyroStart_clicked();
    void on_pushButtonGyroStop_clicked();

    void on_pushButtonGPSSetting_clicked();
    void on_pushButtonGPSApply_clicked();
    void on_pushButtonGPSStart_clicked();
    void on_pushButtonGPSStop_clicked();

    void on_pushButtonSpeedSetting_clicked();
    void on_pushButtonSpeedApply_clicked();
    void on_pushButtonSpeedStart_clicked();
    void on_pushButtonSpeedStop_clicked();

    void on_pushButtonWaterSpeedSetting_clicked();
    void on_pushButtonWaterApply_clicked();
    void on_pushButtonWaterStart_clicked();
    void on_pushButtonWaterStop_clicked();

    void on_pushButtonWindSetting_clicked();
    void on_pushButtonWindApply_clicked();
    void on_pushButtonWindStart_clicked();
    void on_pushButtonWindStop_clicked();

    void on_pushButtonWeatherSetting_clicked();
    void on_pushButtonWeatherApply_clicked();
    void on_pushButtonWeatherStart_clicked();
    void on_pushButtonWeatherStop_clicked();

    void on_pushButtonClear_clicked();

private:
    void gyroState(bool connected);
    void gpsState(bool connected);
    void speedState(bool connected);
    void waterState(bool connected);
    void windState(bool connected);
    void weatherState(bool connected);

    Ui::FrameOSDSet *ui;

    QMap<QString,DialogConfig*> dialogSettingsList;

    //=== Gyrovalue ===//
    double headingGyro;
    double pitchGyro;
    double rollGyro;

    //=== Gpsvalue ===//
    QString latitude;
    QString longitude;
    QString valueLat;
    QString valueLon;

    //=== Speedvalue ===//
    double cogSpeed;
    double sogSpeed;

    //=== Watervalue ===//
    double cogWater;
    double sogWater;

    //=== Windvalue ===//
    double speedWind;
    double dirWind;

    //=== Weather ===//
    double tempWeather;
    double pressWeather;
    double humidityWeather;

    bool isconnected;
    bool activeStart;
    QSerialPort serial;

    QTimer *SendtimerGyro;
    QTimer *SendtimerGps;
    QTimer *SendtimerSpeed;
    QTimer *SendtimerWater;
    QTimer *SendtimerWind;
    QTimer *SendtimerWeather;
};

#endif // FRAMEOSDSET_H
