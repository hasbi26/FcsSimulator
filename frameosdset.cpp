#include "frameosdset.h"
#include "ui_frameosdset.h"
#include <QDebug>
#include <QMessageBox>
#include <unistd.h>
#include "math.h"
#include "iostream"
#include <iomanip>
#include <vector>
#include "QSettings"
#include <QFile>
#include "QDir"


using namespace std;


FrameOSDSet::FrameOSDSet(QWidget *parent) :QFrame(parent),
    ui(new Ui::FrameOSDSet)
{
    ui->setupUi(this);

    //=== Line gyro ===//
    ui->lineEditGyroHeading->setEnabled(false);
    ui->lineEditGyroPitch->setEnabled(false);
    ui->lineEditGyroRoll->setEnabled(false);
    ui->pushButtonGyroApply->setEnabled(false);
    ui->pushButtonGyroStop->setEnabled(false);
    ui->pushButtonGyroStart->setEnabled(false);

    //=== Line gps ===//
    ui->lineEditGpsLat->setEnabled(false);
    ui->lineEditGpsLong->setEnabled(false);
    ui->pushButtonGPSApply->setEnabled(false);
    ui->pushButtonGPSStop->setEnabled(false);
    ui->pushButtonGPSStart->setEnabled(false);

    //=== Line speed ===//
    ui->lineEditSpeedSOG->setEnabled(false);
    ui->lineEditSpeedCOG->setEnabled(false);
    ui->pushButtonSpeedApply->setEnabled(false);
    ui->pushButtonSpeedStop->setEnabled(false);
    ui->pushButtonSpeedStart->setEnabled(false);

    //=== Line waterspeed ===//
    ui->lineEditWaterCOG->setEnabled(false);
    ui->lineEditWaterSOG->setEnabled(false);
    ui->pushButtonWaterApply->setEnabled(false);
    ui->pushButtonWaterStop->setEnabled(false);
    ui->pushButtonWaterStart->setEnabled(false);

    //=== Line wind ===//
    ui->lineEditWindSpeed->setEnabled(false);
    ui->lineEditWindDir->setEnabled(false);
    ui->pushButtonWindApply->setEnabled(false);
    ui->pushButtonWindStop->setEnabled(false);
    ui->pushButtonWindStart->setEnabled(false);

    //=== Line waether ===//
    ui->lineEditWeatherTemp->setEnabled(false);
    ui->lineEditWeatherPress->setEnabled(false);
    ui->lineEditWeatherHumidity->setEnabled(false);
    ui->pushButtonWeatherApply->setEnabled(false);
    ui->pushButtonWeatherStop->setEnabled(false);
    ui->pushButtonWeatherStart->setEnabled(false);

    //=== led ===//
    ui->openCloseLed->turnOff();
    ui->openCloseLed_gps->turnOff();
    ui->openCloseLed_speed->turnOff();
    ui->openCloseLed_water->turnOff();
    ui->openCloseLed_wind->turnOff();
    ui->openCloseLed_weather->turnOff();
    //=== akhir led ===//

    dialogSettingsList.insert("gyroSettings",new DialogConfig(this));
    dialogSettingsList.insert("gpsSettings",new DialogConfig(this));
    dialogSettingsList.insert("speedSettings",new DialogConfig(this));
    dialogSettingsList.insert("waterSpeedSettings",new DialogConfig(this));
    dialogSettingsList.insert("windSettings",new DialogConfig(this));
    dialogSettingsList.insert("weatherSettings",new DialogConfig(this));

}

FrameOSDSet::~FrameOSDSet()
{
    delete ui;
}

//=== Stage OSD ===//
void FrameOSDSet::gyroState(bool connected)
{
    if(connected)
        ui->openCloseLed->turnOn();
    else
        ui->openCloseLed->turnOff();

    ui->lineEditGyroHeading->setEnabled(connected);
    ui->lineEditGyroPitch->setEnabled(connected);
    ui->lineEditGyroRoll->setEnabled(connected);
    ui->pushButtonGyroApply->setEnabled(connected);
}

void FrameOSDSet::gpsState(bool connected)
{
    if(connected)
        ui->openCloseLed_gps->turnOn();
    else
        ui->openCloseLed_gps->turnOff();

    ui->lineEditGpsLat->setEnabled(connected);
    ui->lineEditGpsLong->setEnabled(connected);
    ui->pushButtonGPSApply->setEnabled(connected);
}

void FrameOSDSet::speedState(bool connected)
{
    if(connected)
        ui->openCloseLed_speed->turnOn();
    else
        ui->openCloseLed_speed->turnOff();

    ui->lineEditSpeedSOG->setEnabled(connected);
    ui->lineEditSpeedCOG->setEnabled(connected);
    ui->pushButtonSpeedApply->setEnabled(connected);
}

void FrameOSDSet::waterState(bool connected)
{
    if(connected)
        ui->openCloseLed_water->turnOn();
    else
        ui->openCloseLed_water->turnOff();

    ui->lineEditWaterSOG->setEnabled(connected);
    ui->lineEditWaterCOG->setEnabled(connected);
    ui->pushButtonWaterApply->setEnabled(connected);
}

void FrameOSDSet::windState(bool connected)
{
    if(connected)
        ui->openCloseLed_wind->turnOn();
    else
        ui->openCloseLed_weather->turnOff();

    ui->lineEditWindSpeed->setEnabled(connected);
    ui->lineEditWindDir->setEnabled(connected);
    ui->pushButtonWindApply->setEnabled(connected);
}

void FrameOSDSet::weatherState(bool connected)
{
    if(connected)
        ui->openCloseLed_weather->turnOn();
    else
        ui->openCloseLed_weather->turnOff();

    ui->lineEditWeatherTemp->setEnabled(connected);
    ui->lineEditWeatherPress->setEnabled(connected);
    ui->lineEditWeatherHumidity->setEnabled(connected);
    ui->pushButtonWeatherApply->setEnabled(connected);
}

//=== Button Setting ===//
void FrameOSDSet::on_pushButtonGyroSetting_clicked()
{
    DialogConfig *dialogGyro = dialogSettingsList.value("gyroSettings");
    dialogGyro->show();

    qDebug()<<"list"<<dialogSettingsList.value("gyroSettings");
    qDebug()<< "YYY"<< dialogSettingsList;

    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Gyro");
    qDebug()<<"PortnameGyro =" << settings.value("portname");
    dialogGyro->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                  settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                  settings.value("tcpip").toString(), settings.value("tcpport").toString());

    if (dialogGyro->exec() == QDialog::Accepted)
    {

        qDebug()<<"PortnameGyro =" << dialogGyro->GetPortname();
        activeStart = true;
        if (ui->osdGryoComboBox->currentText() == "Serial"){
            settings.setValue("portname", dialogGyro->GetPortname());
            settings.setValue("baud", dialogGyro->GetBaud());
            settings.setValue("stopbits", dialogGyro->GetStopBit());
            settings.setValue("databits", dialogGyro->GetDatabit());
            settings.setValue("parity", dialogGyro->GetParity());
            gyroState(dialogGyro->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogGyro->GetTcp());
            settings.setValue("tcpport", dialogGyro->GetPort());
            gyroState(dialogGyro->tcpconnected());
        }
    }
    settings.endGroup();

}

void FrameOSDSet::on_pushButtonGPSSetting_clicked()
{
    DialogConfig *dialogGps = dialogSettingsList.value("gpsSettings");
    dialogGps->show();

    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Gps");
    dialogGps->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                 settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                 settings.value("tcpip").toString(), settings.value("tcpport").toString());


    if (dialogGps->exec() == QDialog::Accepted)
    {
          activeStart = true;
        if (ui->comboBoxGPSMode->currentText() == "Serial"){
            settings.setValue("portname", dialogGps->GetPortname());
            settings.setValue("baud", dialogGps->GetBaud());
            settings.setValue("stopbits", dialogGps->GetStopBit());
            settings.setValue("databits", dialogGps->GetDatabit());
            settings.setValue("parity", dialogGps->GetParity());
            gpsState(dialogGps->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogGps->GetTcp());
            settings.setValue("tcpport", dialogGps->GetPort());
            gpsState(dialogGps->tcpconnected());
            }
    }
}

void FrameOSDSet::on_pushButtonSpeedSetting_clicked()
{
    DialogConfig *dialogSpeed = dialogSettingsList.value("speedSettings");
    dialogSpeed->show();


    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Speed");
    dialogSpeed->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                   settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                   settings.value("tcpip").toString(), settings.value("tcpport").toString());


    if (dialogSpeed->exec() == QDialog::Accepted)
    {
        activeStart = true;
        if (ui->comboBoxSpeedMode->currentText() == "Serial"){
            settings.setValue("portname", dialogSpeed->GetPortname());
            settings.setValue("baud", dialogSpeed->GetBaud());
            settings.setValue("databits", dialogSpeed->GetDatabit());
            settings.setValue("stopbits", dialogSpeed->GetStopBit());
            settings.setValue("parity", dialogSpeed->GetParity());
            speedState(dialogSpeed->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogSpeed->GetTcp());
            settings.setValue("tcpport", dialogSpeed->GetPort());
            speedState(dialogSpeed->tcpconnected());
            }
    }
}

void FrameOSDSet::on_pushButtonWaterSpeedSetting_clicked()
{
    DialogConfig *dialogWater = dialogSettingsList.value("waterSpeedSettings");
    dialogWater->show();


    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Water");
    dialogWater->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                   settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                   settings.value("tcpip").toString(), settings.value("tcpport").toString());

    if (dialogWater->exec() == QDialog::Accepted)
    {
        activeStart = true;
        if (ui->comboBoxWaterMode->currentText() == "Serial"){
            settings.setValue("portname", dialogWater->GetPortname());
            settings.setValue("baud", dialogWater->GetBaud());
            settings.setValue("databits", dialogWater->GetDatabit());
            settings.setValue("stopbits", dialogWater->GetStopBit());
            settings.setValue("parity", dialogWater->GetParity());
            waterState(dialogWater->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogWater->GetTcp());
            settings.setValue("tcpport", dialogWater->GetPort());
            waterState(dialogWater->tcpconnected());
        }
    }
}

void FrameOSDSet::on_pushButtonWindSetting_clicked()
{
    DialogConfig *dialogWind = dialogSettingsList.value("windSettings");
    dialogWind->show();

    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Wind");
    dialogWind->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                  settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                  settings.value("tcpip").toString(), settings.value("tcpport").toString());

    if (dialogWind->exec() == QDialog::Accepted)
    {
        activeStart = true;
        if (ui->comboBoxWindMode->currentText() == "Serial"){
            settings.setValue("portname", dialogWind->GetPortname());
            settings.setValue("baud", dialogWind->GetBaud());
            settings.setValue("databits", dialogWind->GetDatabit());
            settings.setValue("stopbits", dialogWind->GetStopBit());
            settings.setValue("parity", dialogWind->GetParity());
            windState(dialogWind->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogWind->GetTcp());
            settings.setValue("tcpport", dialogWind->GetPort());
            windState(dialogWind->tcpconnected());
            }
    }
}

void FrameOSDSet::on_pushButtonWeatherSetting_clicked()
{
    DialogConfig *dialogWeather = dialogSettingsList.value("weatherSettings");
    dialogWeather->show();

    QSettings settings("app.ini", QSettings::IniFormat);
    settings.beginGroup("Weather");
    dialogWeather->setSerialSettings(settings.value("portname").toString(), settings.value("baud").toString(),
                                     settings.value("stopbits").toString(), settings.value("databits").toString(), settings.value("parity").toString(),
                                     settings.value("tcpip").toString(), settings.value("tcpport").toString());

    if (dialogWeather->exec() == QDialog::Accepted)
    {

        activeStart = true;
        if (ui->comboBoxWeatherMode->currentText() == "Serial"){

            settings.setValue("portname", dialogWeather->GetPortname());
            settings.setValue("baud", dialogWeather->GetBaud());
            settings.setValue("databits", dialogWeather->GetDatabit());
            settings.setValue("stopbits", dialogWeather->GetStopBit());
            settings.setValue("parity", dialogWeather->GetParity());
            weatherState(dialogWeather->serialconnected());
        }
        else{
            settings.setValue("tcpip", dialogWeather->GetTcp());
            settings.setValue("tcpport", dialogWeather->GetPort());
            weatherState(dialogWeather->tcpconnected());
        }
    }
}

//=== Button Apply ===//
void FrameOSDSet::on_pushButtonGyroApply_clicked()
{
    headingGyro = ui->lineEditGyroHeading->text().toDouble();
    pitchGyro = ui->lineEditGyroPitch->text().toDouble();
    rollGyro = ui->lineEditGyroRoll->text().toDouble();

    QString heading = ui->lineEditGyroHeading->text();
    QString roll = ui->lineEditGyroRoll->text();
    QString pitch = ui->lineEditGyroPitch->text();
    qDebug()<<"heading = "<<headingGyro<<"pitch = "<<pitchGyro<<"roll = " <<rollGyro<<endl;
    if (activeStart == true)
    {
        ui->pushButtonGyroStart->setEnabled(true);

    }
    ui->pushButtonGyroSetting->setEnabled(false);

    bool ok;

    float heading_float = heading.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Heading", "Invalid input value\nValid input range : 0 - 360" );
        return;
    }
    if ((heading_float < 0) || (heading_float > 360) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid heading input\nValid input range : 0 - 360" );
        return;
    }

    float roll_float = roll.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Roll", "Invalid input value\nValid input range : -30 to 30" );
        return;
    }
    if ((roll_float < -30) || (roll_float > 30) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid roll input\nValid input range : -30 to 30" );
        return;
    }

    float pitch_float = pitch.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Pitch", "Invalid input value\nValid input range : -30 to 30" );
        return;
    }
    if ((pitch_float < -30) || (pitch_float > 30) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid pitch input\nValid input range : -30 to 30" );
        return;
    }
}

void FrameOSDSet::on_pushButtonGPSApply_clicked()
{

    if (activeStart == true)
    {
        ui->pushButtonGPSStart->setEnabled(true);
    }
    ui->pushButtonGPSSetting->setEnabled(false);

    //gps string : 20-30'36''S
    //gps desimal : -20.5100000 (20 + 30/60 + 36/3600)
    //gps desimal : -20.5100000 (20 + 0.5 + 0.01)
    //gps nmea: 2051.0000,S

    // ==== Float latitude ====

    if (ui->lineEditGpsLat->text() != "0.0 S")

    {
        qDebug()<<"tetot";
        qDebug()<< "latitude :" << ui->lineEditGpsLat->text() ;

        QString lat = ui->lineEditGpsLat->text();
        valueLat = lat.split("'").at(3);
        float derajat = lat.split("-").at(0).toFloat();
        float menit = lat.split("'").at(0).split("-").at(1).toFloat();
        float detik = lat.split("'").at(1).toFloat();
        float GpsDesimal;
        if (valueLat == "S")
        {
            GpsDesimal = (derajat + menit/60 + detik/3600)* -1;
            double Formating = GpsDesimal * -100;
            latitude = QString::number(Formating,'f',4);
            QString str= QString::number(Formating, 'f', 4);
        }
        else{
            GpsDesimal = (derajat + menit/60 + detik/3600);
            double Formating1 = GpsDesimal * 100;
            latitude = QString::number(Formating1,'f',4);
            QString str= QString::number(Formating1, 'f', 4);
        }
        qDebug()<< "latitude = "<< latitude << valueLat;

        // ==== Float longitude ====
        QString lon = ui->lineEditGpsLong->text();
        valueLon = lon.split("'").at(3);
        float derajatlon = lon.split("-").at(0).toFloat();
        float menitlon = lon.split("'").at(0).split("-").at(1).toFloat();
        float detiklon = lon.split("'").at(1).toFloat();
        float GpsDesimallon;
        if (valueLon == "W")
        {
            GpsDesimallon = (derajatlon + menitlon/60 + detiklon/3600)* -1;
            double Formatinglon = GpsDesimallon * -100;
            if (QString::number(Formatinglon).length() ==  4)
            {
                longitude = "0"+QString::number(Formatinglon,'f',4);

            } else if (QString::number(Formatinglon).length() ==  3)
            {
                longitude = "00"+QString::number(Formatinglon,'f',4);

            } else if (QString::number(Formatinglon).length() ==  5)
            {
                longitude = QString::number(Formatinglon,'f',4);
            }


    qDebug()<<"formatilon" <<QString::number(Formatinglon).length();

        }
        else{
            GpsDesimallon = (derajatlon + menitlon/60 + detiklon/3600);
            double Formatinglon1 = GpsDesimallon * 100;

            qDebug()<< "lenght" << QString::number(Formatinglon1).length();

            if (QString::number(Formatinglon1).length() ==  5)
            {
                longitude = ""+QString::number(Formatinglon1,'f',4);

            } else if (QString::number(Formatinglon1).length() ==  4)
            {
                longitude = "0"+QString::number(Formatinglon1,'f',4);

            } else if (QString::number(Formatinglon1).length() ==  3)
            {
                longitude = "00"+QString::number(Formatinglon1,'f',4);
            }

        }
        qDebug()<< "longitude = "<< longitude << valueLon;

        // ==== Float latitude Notif ====
    //    if (ui->lineEditGpsLat->text() != )

        QString lat_str_trimmed = ui->lineEditGpsLat->text();
        lat_str_trimmed.remove(" ");

        QString str = lat_str_trimmed;
        QStringList list1 = str.split("-");
        if(list1.size()<2)
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid input value.\nValid input : -" );
            return;
        }

        QString deg1 = list1.at(0);
        QStringList list2 = list1.at(1).split("'");
        if(list2.size()!=4)
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid input value.\nValid input : '" );
            return;
        }

        QString min1 = list2.at(0);
        QString sec1 = list2.at(1);
        QString sign = list2.at(3);
//            qDebug() << deg  <<min <<sec <<sign;
        qDebug()<<"sign adalah" << sign;

        bool ok;
        float valuedeg = deg1.toFloat(&ok);
        if (!ok)
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid degree input value.\nValid input : 00-90" );
            return;
        }

        float valuemin = min1.toFloat(&ok)/60.0;
        if ((!ok) || (valuemin >= 1))
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid minute input value.\nValid input : 00-59" );
            return;
        }

        float valuesec = sec1.toFloat(&ok)/3600.0;
        if ((!ok) || (valuesec > (1.0/60.0)))
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid second input value.\nValid input : 00-59" );
            return;
        }

        float valueLat = valuedeg+valuemin+valuesec;

        if(sign == "S")
            valueLat *= -1.0;
        else if((sign != "S") && (sign != "N"))
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid orientation input value.\nValid input : S/N" );
            return;
        }

        if ((valueLat < -90) || (valueLat > 90) )
        {
            QMessageBox::critical(this, "Fatal Error Latitude", "Invalid input : out of range.\nValid input : 00-00'00'' - 90-00'00''");
            return;
        }

        //    qDebug() << Q_FUNC_INFO<<valuedeg << valuemin <<valuesec <<valueLat;

        // ==== Float longitude ====

        QString long_str_trimmed = ui->lineEditGpsLong->text();
        long_str_trimmed.remove(" ");

        QString str1 = long_str_trimmed;
        QStringList long_list1 = str1.split("-");
        if(long_list1.size()<2)
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid input value.\nValid input : -" );
            return;
        }

        QString degg = long_list1.at(0);
        QStringList long_list2 = long_list1.at(1).split("'");
        if(long_list2.size()!=4)
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid input value.\nValid input : '" );
            return;
        }

        QString minn = long_list2.at(0);
        QString secc = long_list2.at(1);
        QString signn = long_list2.at(3);
        //    qDebug() <<degg  <<minn <<secc <<signn;

        bool ok1;
        float valuedegg = degg.toFloat(&ok1);
        if (!ok1)
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid degree input value.\nValid input : 00-180" );
            return;
        }

        float valueminn = minn.toFloat()/60.0;
        if ((!ok) || (valueminn >= 1))
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid minute input value.\nValid input : 00-59" );
            return;
        }

        float valuesecc = secc.toFloat()/3600.0;
        if ((!ok) || (valuesecc > (1.0/60.0)))
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid second input value.\nValid input : 00-59" );
            return;
        }

        float valueLong = valuedegg+valueminn+valuesecc;

//        if(signn == "W")
//            valueLong *= -1.0;
//        else if ((signn != "W") && (signn != "E"))
//        {
//            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid orientation input value.\nValid input : W/E" );
//            return;
//        }

        if ((valueLong < -180) || (valueLong > 180) )
        {
            QMessageBox::critical(this, "Fatal Error Longitude", "Invalid input : out of range.\nValid input : 00-00'00'' - 180-00'00''" );
            return;
        }
    }
    else
    {
        QMessageBox::critical(this, "Fatal Error Latitude", "the field is empty" );
    }
}

void FrameOSDSet::on_pushButtonSpeedApply_clicked()
{
    sogSpeed = ui->lineEditSpeedSOG->text().toDouble();
    cogSpeed = ui->lineEditSpeedCOG->text().toDouble();

    QString sog = ui->lineEditSpeedSOG->text();
    QString cog = ui->lineEditSpeedCOG->text();
    qDebug()<<"cogSpeed = "<<sogSpeed<<"sogSpeed = "<<cogSpeed<<endl;
    if (activeStart == true)
    {
        ui->pushButtonSpeedStart->setEnabled(true);
    }
    ui->pushButtonSpeedSetting->setEnabled(false);

    bool ok;

    float sog_float =sog. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Speed SOG", "Invalid input value\nValid input range : 0 to 150" );
        return;
    }
    if ((sog_float < 0) || (sog_float > 150) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid speed sog input\nValid input range : 0 to 150" );
        return;
    }

    float cog_float =cog. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Speed COG", "Invalid input value\nValid input range : 0 - 360" );
        return;
    }
    if ((cog_float < 0) || (cog_float > 360) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid speed cog input\nValid input range : 0 - 360" );
        return;
    }
}

void FrameOSDSet::on_pushButtonWaterApply_clicked()
{
    sogWater = ui->lineEditWaterSOG->text().toDouble();
    cogWater = ui->lineEditWaterCOG->text().toDouble();

    QString speed = ui->lineEditWaterSOG->text();
    QString course = ui->lineEditWaterCOG->text();
    qDebug()<<"cogWater = "<<sogWater<<"sogWater = "<<cogWater<<endl;
    if (activeStart == true)
    {
        ui->pushButtonWaterStart->setEnabled(true);
    }
    ui->pushButtonWaterSpeedSetting->setEnabled(false);

    bool ok;

    float speed_float =speed. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Water Speed", "Invalid input value\nValid input range : -150 - 150" );
        return;
    }
    if ((speed_float < -150) || (speed_float > 150) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid water speed input\nValid input range : -150 - 150" );
        return;
    }

    float course_float =course. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Water Course", "Invalid input value\nValid input range : 0 - 360" );
        return;
    }
    if ((course_float < 0) || (course_float > 360) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid water course input\nValid input range : 0 - 360" );
        return;
    }
}

void FrameOSDSet::on_pushButtonWindApply_clicked()
{
    speedWind = ui->lineEditWindSpeed->text().toDouble();
    dirWind = ui->lineEditWindDir->text().toDouble();

    QString dir = ui->lineEditWindDir->text();
    QString speed = ui->lineEditWindSpeed->text();
    qDebug()<<"speedWind = "<<speedWind<<"dirWind = "<<dirWind<<endl;
    if (activeStart == true)
    {
        ui->pushButtonWindStart->setEnabled(true);
    }
    ui->pushButtonWindSetting->setEnabled(false);

    bool ok;

    float dir_float = dir.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Wind Direction", "Invalid input value\nValid input range : 0 - 360" );
        return;
    }
    if ((dir_float < 0) || (dir_float > 360) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid wind direction value\nValid input range : 0 - 360" );
        return;
    }

    float speed_float =speed.toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Wind Speed", "Invalid input value\nValid input range : -150 to 150" );
        return;
    }
    if ((speed_float < -150) || (speed_float > 150) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid wind speed input\nValid input range : -150 to 150" );
        return;
    }
}

void FrameOSDSet::on_pushButtonWeatherApply_clicked()
{
    tempWeather = ui->lineEditWeatherTemp->text().toDouble();
    pressWeather = ui->lineEditWeatherPress->text().toDouble();
    humidityWeather = ui->lineEditWeatherHumidity->text().toDouble();

    QString temperature = ui->lineEditWeatherTemp->text();
    QString pressure = ui->lineEditWeatherPress->text();
    QString humidity = ui->lineEditWeatherHumidity->text();
    qDebug()<<"tempWeather = "<<tempWeather<<"pressWeather = "<<pressWeather <<"humidityWeather = "<<humidityWeather <<endl;
    if (activeStart == true)
    {
        ui->pushButtonWeatherStart->setEnabled(true);
    }
    ui->pushButtonWeatherSetting->setEnabled(false);

    bool ok;

    float temperature_float =temperature. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Weather Temperature", "Invalid input value\nValid input range : -273 to 273" );
        return;
    }
    if ((temperature_float < -273) || (temperature_float > 273) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid weather temperature input\nValid input range : -273 to 273" );
        return;
    }

    float pressure_float =pressure. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Weather Pressure", "Invalid input value\nValid input range : 100 - 1000" );
        return;
    }
    if ((pressure_float < 0.1) || (pressure_float > 100) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid weather pressure input\nValid input range : 100 - 10000" );
        return;
    }

    float humidity_float =humidity. toFloat(&ok);
    if(!ok)
    {
        QMessageBox::critical(this, "Fatal Error Weather Humidity", "Invalid input value\nValid input range : 0 - 100" );
        return;
    }

    if ((humidity_float < 0) || (humidity_float > 100) )
    {
        QMessageBox::critical(this, "Fatal Error", "Invalid Weather humidity input\nValid input range : 0 - 100" );
        return;
    }
}

//=== Button Start ===//
void FrameOSDSet::on_pushButtonGyroStart_clicked()
{
    activeStart = false;
    ui->pushButtonGyroStop->setEnabled(true);
    ui->pushButtonGyroStart->setEnabled(false);
    ui->pushButtonGyroApply->setEnabled(true);
    ui->pushButtonGyroSetting->setEnabled(false);
    SendtimerGyro = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerGyro->setInterval( sendInterval );
    connect(SendtimerGyro, SIGNAL(timeout()),this, SLOT(on_GyroTimer()));
    SendtimerGyro->start(sendInterval);
}

void FrameOSDSet::on_pushButtonGPSStart_clicked()
{
    activeStart = false;
    ui->pushButtonGPSStop->setEnabled(true);
    ui->pushButtonGPSStart->setEnabled(false);
    ui->pushButtonGPSApply->setEnabled(true);
    ui->pushButtonGPSSetting->setEnabled(false);
    SendtimerGps = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerGps->setInterval( sendInterval );
    connect(SendtimerGps, SIGNAL(timeout()),this, SLOT(on_GpsTimer()));
    SendtimerGps->start(sendInterval);
}

void FrameOSDSet::on_pushButtonSpeedStart_clicked()
{
    activeStart = false;
    ui->pushButtonSpeedStop->setEnabled(true);
    ui->pushButtonSpeedStart->setEnabled(false);
    ui->pushButtonSpeedApply->setEnabled(true);
    ui->pushButtonSpeedSetting->setEnabled(false);
    SendtimerSpeed = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerSpeed->setInterval( sendInterval );
    connect(SendtimerSpeed, SIGNAL(timeout()),this, SLOT(on_SpeedTimer()));
    SendtimerSpeed->start(sendInterval);
}

void FrameOSDSet::on_pushButtonWaterStart_clicked()
{
    activeStart = false;
    ui->pushButtonWaterStop->setEnabled(true);
    ui->pushButtonWaterStart->setEnabled(false);
    ui->pushButtonWaterApply->setEnabled(true);
    ui->pushButtonWaterSpeedSetting->setEnabled(false);
    SendtimerWater = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerWater->setInterval( sendInterval );
    connect(SendtimerWater, SIGNAL(timeout()),this, SLOT(on_WaterTimer()));
    SendtimerWater->start(sendInterval);
}

void FrameOSDSet::on_pushButtonWindStart_clicked()
{
    activeStart = false;
    ui->pushButtonWindStop->setEnabled(true);
    ui->pushButtonWindStart->setEnabled(false);
    ui->pushButtonWindApply->setEnabled(true);
    ui->pushButtonWindSetting->setEnabled(false);
    SendtimerWind = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerWind->setInterval( sendInterval );
    connect(SendtimerWind, SIGNAL(timeout()),this, SLOT(on_WindTimer()));
    SendtimerWind->start(sendInterval);
}

void FrameOSDSet::on_pushButtonWeatherStart_clicked()
{
    activeStart = false;
    ui->pushButtonWeatherStop->setEnabled(true);
    ui->pushButtonWeatherStart->setEnabled(false);
    ui->pushButtonWeatherApply->setEnabled(true);
    ui->pushButtonWeatherSetting->setEnabled(false);
    SendtimerWeather = new QTimer( this );
    int sendInterval = 500; // milliseconds
    SendtimerWeather->setInterval( sendInterval );
    connect(SendtimerWeather, SIGNAL(timeout()),this, SLOT(on_WeatherTimer()));
    SendtimerWeather->start(sendInterval);
}

//=== Button Stop ===//
void FrameOSDSet::on_pushButtonGyroStop_clicked()
{
    activeStart = true;
    ui->pushButtonGyroStop->setEnabled(true);
    ui->pushButtonGyroStart->setEnabled(false);
    ui->pushButtonGyroApply->setEnabled(true);
    ui->pushButtonGyroSetting->setEnabled(true);
    SendtimerGyro->stop();

    DialogConfig *Gyro = dialogSettingsList.value("gyroSettings");
    Gyro->disconnected();
}

void FrameOSDSet::on_pushButtonGPSStop_clicked()
{
    activeStart = true;
    ui->pushButtonGPSStop->setEnabled(false);
    ui->pushButtonGPSStart->setEnabled(false);
    ui->pushButtonGPSApply->setEnabled(true);
    ui->pushButtonGPSSetting->setEnabled(true);
    SendtimerGps->stop();
    DialogConfig *Gps = dialogSettingsList.value("gpsSettings");
    Gps->disconnected();
}

void FrameOSDSet::on_pushButtonSpeedStop_clicked()
{
    activeStart = true;
    ui->pushButtonSpeedStop->setEnabled(false);
    ui->pushButtonSpeedStart->setEnabled(false);
    ui->pushButtonSpeedApply->setEnabled(true);
    ui->pushButtonSpeedSetting->setEnabled(true);
    SendtimerSpeed->stop();
    DialogConfig *speed = dialogSettingsList.value("speedSettings");
    speed->disconnected();
}

void FrameOSDSet::on_pushButtonWaterStop_clicked()
{
    activeStart = true;
    ui->pushButtonWaterStop->setEnabled(false);
    ui->pushButtonWaterStart->setEnabled(false);
    ui->pushButtonWaterApply->setEnabled(true);
    ui->pushButtonWaterSpeedSetting->setEnabled(true);
    SendtimerWater->stop();
    DialogConfig *Water = dialogSettingsList.value("waterSpeedSettings");
    Water->disconnected();
}

void FrameOSDSet::on_pushButtonWindStop_clicked()
{
    activeStart = true;
    ui->pushButtonWindStop->setEnabled(false);
    ui->pushButtonWindStart->setEnabled(false);
    ui->pushButtonWindApply->setEnabled(true);
    ui->pushButtonWindSetting->setEnabled(true);
    SendtimerWind->stop();
    DialogConfig *Wind = dialogSettingsList.value("windSettings");
    Wind->disconnected();
}

void FrameOSDSet::on_pushButtonWeatherStop_clicked()
{
    activeStart = true;
    ui->pushButtonWeatherStop->setEnabled(false);
    ui->pushButtonWeatherStart->setEnabled(false);
    ui->pushButtonWeatherApply->setEnabled(true);
    ui->pushButtonWeatherSetting->setEnabled(true);
    SendtimerWeather->stop();
    DialogConfig *Weather = dialogSettingsList.value("weatherSettings");
    Weather->disconnected();
    qDebug()<<"Weather disconected";
}

//=== Timer ===//
void FrameOSDSet::on_GyroTimer()
{
    DialogConfig *dialogGyro = dialogSettingsList.value("gyroSettings");
    Nmeagenerator* nmeaGyro = new Nmeagenerator();
    QString Datatosend = nmeaGyro->constructDataGyro(headingGyro, pitchGyro, rollGyro);
    if (ui->osdGryoComboBox->currentText() == "Serial")
    {
        if (dialogGyro->GetPortname().isEmpty())
        {
            qDebug()<<"portname Kosong";
        } else
        {
            qDebug()<<"Dataserial Gyro Kirim =" << Datatosend;
            ui->textEdit->insertPlainText(Datatosend);
            dialogGyro->SerialWrite(Datatosend);
        }

    }
    else
    {
        qDebug()<<"DataTcp Gyro Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogGyro->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_GpsTimer()
{
    DialogConfig *dialogGps = dialogSettingsList.value("gpsSettings");
    Nmeagenerator* nmeaGps = new Nmeagenerator();
    QString Datatosend = nmeaGps->constructDataGps(latitude,longitude, valueLat, valueLon);
    if (ui->comboBoxGPSMode->currentText() == "Serial")
    {
        qDebug()<<"Dataserial Gps Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogGps->SerialWrite(Datatosend);
    }
    else if (ui->comboBoxGPSMode->currentText() == "TCP")
    {
        qDebug()<<"DataTcp Gps Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogGps->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_SpeedTimer()
{
    DialogConfig *dialogSpeed = dialogSettingsList.value("speedSettings");
    Nmeagenerator* nmeaSpeed = new Nmeagenerator();
    QString Datatosend = nmeaSpeed->constructDataSpeed(sogSpeed,cogSpeed);
    if (ui->comboBoxSpeedMode->currentText() == "Serial")
    {
        qDebug()<<"Dataserial Speed Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogSpeed->SerialWrite(Datatosend);
    }
    else
    {
        qDebug()<<"DataTcp Speed Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogSpeed->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_WaterTimer()
{
    Nmeagenerator* nmeaWater = new Nmeagenerator();
    DialogConfig *dialogWater = dialogSettingsList.value("waterSpeedSettings");
    QString Datatosend = nmeaWater->constructDataWater(sogWater,cogWater);
    if (ui->comboBoxWaterMode->currentText() == "Serial")
    {
        qDebug()<<"Dataserial WaterSpeed Kirim =" << Datatosend;

        ui->textEdit->insertPlainText(Datatosend);
        dialogWater->SerialWrite(Datatosend);
    }
    else
    {
        qDebug()<<"Datatcp WaterSpeed Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogWater->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_WindTimer()
{
    DialogConfig *dialogWind = dialogSettingsList.value("windSettings");
    Nmeagenerator* nmeaWind = new Nmeagenerator();
    QString Datatosend = nmeaWind->constructDataWind(speedWind,dirWind);
    if (ui->comboBoxWindMode->currentText() == "Serial")
    {
        qDebug()<<"Dataserial Wind Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogWind->SerialWrite(Datatosend);
    }
    else
    {
        qDebug()<<"Datatcp Wind Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogWind->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_WeatherTimer()
{
    DialogConfig *dialogWeather = dialogSettingsList.value("weatherSettings");
    Nmeagenerator* nmeaWeather = new Nmeagenerator();
    QString Datatosend = nmeaWeather->constructDataWeather(tempWeather,pressWeather,humidityWeather);
    if (ui->comboBoxWeatherMode->currentText() == "Serial")
    {
        qDebug()<<"Dataserial Weather Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogWeather->SerialWrite(Datatosend);
    }
    else
    {
        qDebug()<<"Datatcp Weather Kirim =" << Datatosend;
        ui->textEdit->insertPlainText(Datatosend);
        dialogWeather->TcpWrite(Datatosend);
    }
}

void FrameOSDSet::on_pushButtonClear_clicked()
{
    ui->textEdit->clear();
}

