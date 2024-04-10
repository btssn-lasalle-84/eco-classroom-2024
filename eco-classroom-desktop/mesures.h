#ifndef MESURES_H
#define MESURES_H

#include <QDateTime>

class Mesures
{
  private:
    int       co2;
    double    temperature;
    int       humidite;
    QDateTime horodatage;

  public:
    Mesures();
    ~Mesures();

    int       getCO2() const;
    double    getTemperature() const;
    int       getHumidite() const;
    QDateTime getHorodatage() const;

    void setCO2(co2);
    void setTemperature(temperature);
    void setHumidite(humidite);
    void setHorodatage(QDateTime);
};

#endif // MESURES_H
