#ifndef MESURES_H
#define MESURES_H

#include <QDateTime>

struct MesureCO2
{
    int       co2;
    QDateTime horodatage;
    bool      valide = false;
};

struct MesureTemperature
{
    double    temperature;
    QDateTime horodatage;
    bool      valide = false;
};

struct MesureHumidite
{
    int       humidite;
    QDateTime horodatage;
    bool      valide = false;
};

#endif // MESURES_H
