#ifndef NMEAGENERATOR_H
#define NMEAGENERATOR_H

#include <QObject>
#include <QDebug>

#include <sstream>
#include <string.h>
#include <stdio.h>
#include <QStringList>

class Nmeagenerator : public QObject
{
    Q_OBJECT
public:
    explicit Nmeagenerator(QObject *parent = nullptr);

    QString constructDataGyro(double& heading, double& pitch, double& roll);
    QString constructDataGps(QString lat, QString lon, QString valuelat, QString valuelon);
    QString constructDataSpeed(double sogspeed, double cogspeed);
    QString constructDataWater(double sogwater, double cogwater);
    QString constructDataWind(double speedwind, double dirwind);
    QString constructDataWeather(double tempweather, double pressweather ,double humidityweather);

    QString getChecksumValue(QString data);

signals:
};

#endif // NMEAGENERATOR_H
