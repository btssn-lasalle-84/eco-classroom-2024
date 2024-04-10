#include "mesures.h"
#include <QDebug>

Mesures::Mesures() : co2(0), temperature(0.), humidite(0), horodatage(QDateTime::currentDateTime())
{
    qDebug() << Q_FUNC_INFO << "horodatage" << horodatage.toString("hh:mm:ss");
}

Mesures::~Mesures()
{
    qDebug() << Q_FUNC_INFO;
}

int Mesures::getCO2() const
{
    return co2;
}

double Mesures::getTemperature() const
{
    return temperature;
}

int Mesures::getHumidite() const
{
    return humidite;
}

QDateTime Mesures::getHorodatage() const
{
    return horodatage;
}

void Mesures::setCO2(co2)
{
    this->co2 = co2;
}

void Mesures::setTemperature(temperature)
{
    this->temperature = temperature;
}

void Mesures::setHumidite(humidite)
{
    this->humidite = humidite;
}

void Mesures::setHorodatage(QDateTime)
{
    this->horodatage = horodatage;
}
