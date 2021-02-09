#include "nmeagenerator.h"

Nmeagenerator::Nmeagenerator(QObject *parent) : QObject(parent)
{

}

QString Nmeagenerator::getChecksumValue(QString data)
{
    unsigned char checksum_value = 0;
    char str_ascii[150];
    strncpy(str_ascii, data.toUtf8().constData(),149);
    str_ascii[150]='\0';
    int string_length = strlen(str_ascii);
    int index = 0;
    // qDebug()<< "ascii =" << str_ascii;
    while (index < string_length  &&
           str_ascii[index] != '*') //&&
        //                 str_ascii[index] != CARRIAGE_RETURN &&
        //                 str_ascii[index] != LINE_FEED)
    {
        checksum_value ^= str_ascii[index];
        index++;
    }
    QString hexadecimal;
    hexadecimal.setNum(checksum_value,16);
    if(hexadecimal.length() %2)hexadecimal.insert(0,QLatin1String("0"));
    //qDebug()<<"checksum"<<hexadecimal.toUpper();
    return(hexadecimal.toUpper());
}

QString Nmeagenerator::constructDataGyro(double& heading, double& pitch, double& roll)
{
    QString data = QString("GPFPD,0.0,0.0,%1,%2,%3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0").arg(heading).arg(pitch).arg(roll);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataGps(QString lat, QString lon, QString valuelat, QString valuelon)
{
    QString data = QString("GPGGA,0,%1,%2,%3,%4,0,0,0.0,0.0,M,0.0,M,0.0,0.0").arg(lat).arg(valuelat).arg(lon).arg(valuelon);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataSpeed(double sogspeed, double cogspeed)
{
    QString data = QString("GPVTG,0.0,T,%1,M,0.0,N,%2,K,a").arg(sogspeed).arg(cogspeed);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataWater(double sogwater, double cogwater)
{
    QString data = QString("IIVHW,0.0,T,%1,M,0.0,N,%2,K").arg(sogwater).arg(cogwater);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataWind(double speedwind, double dirwind)
{
    QString data = QString("IIMWD,0.0,T,%1,M,%2,N,0.0,M").arg(speedwind).arg(dirwind);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataWeather(double tempweather, double pressweather, double humidityweather)
{
    QString data = QString("WIXDR,P.%1,B,0,C,%2,C,0,H,%3,P,0,C,0.0,C,1").arg(tempweather).arg(pressweather).arg(humidityweather);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

