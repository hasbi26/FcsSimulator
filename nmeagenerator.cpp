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
    QString data1 = QString("GPGGA,0,%1,%2,%3,%4,0,0,0.0,0.0,M,0.0,M,0.0,0.0").arg(lat).arg(valuelat).arg(lon).arg(valuelon);
    QString data2 = QString("GPZDA,181813,14,10,2003,00,00").arg(lat).arg(valuelat).arg(lon).arg(valuelon);
    QString checksum =  getChecksumValue(data1);
    QString checksum2 =  getChecksumValue(data2);
    return "$" + data1  + "*" + checksum + "\r\n"+
            "$"+ data2 + "*" + checksum2 + "\r\n";


}

QString Nmeagenerator::constructDataSpeed(double sogspeed, double cogspeed)
{
    QString data = QString("GPVTG,%2,T,0.0,M,%1,N,0.0,K,a").arg(sogspeed).arg(cogspeed);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

QString Nmeagenerator::constructDataWater(double sogwater, double cogwater)
{
    QString data1 = QString("IIVHW,%2,T,0.0,M,%1,N,0.0,K").arg(sogwater).arg(cogwater);
    QString data2 = QString("IIVDR,%2,T,0.0,M,%1,N,0.0,K").arg(sogwater).arg(cogwater);
    QString data3 = QString("IIDPT,%1,0.0").arg(sogwater);
    QString checksum1 =  getChecksumValue(data1);
    QString checksum2 = getChecksumValue(data2);
    QString checksum3 = getChecksumValue(data3);

    return "$" + data1  + "*" + checksum1 + "\r\n"+
            "$" + data2  + "*" + checksum2 + "\r\n"+
            "$" + data3  + "*" + checksum3 + "\r\n";
}

QString Nmeagenerator::constructDataWind(double speedwind, double dirwind)
{
    QString data1 = QString("IIMWV,%2,T,%1,N,A").arg(speedwind).arg(dirwind);
    QString data2 = QString("IIMWV,%2,R,%1,M,A").arg(speedwind).arg(dirwind);
//    QString data2 = QString("IIMWV,%2,R,0.0,M,%1,N,0.0,M").arg(speedwind).arg(dirwind);
    QString checksum1 =  getChecksumValue(data1);
    QString checksum2 = getChecksumValue(data2);
    return "$" + data1  + "*" + checksum1 + "\r\n"+
           "$" + data2  + "*" + checksum2 + "\r\n";
}

QString Nmeagenerator::constructDataWeather(double tempweather, double pressweather, double humidityweather)
{
    QString data = QString("WIXDR,P,%2,B,Barometer,C,%1,C,AirTemp,H,%3,P,Humidity").arg(tempweather).arg(pressweather).arg(humidityweather);
    QString checksum =  getChecksumValue(data);
    return "$" + data  + "*" + checksum + "\r\n";
}

