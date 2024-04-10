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

    void setCO2(int co2);
    void setTemperature(double temperature);
    void setHumidite(int humidite);
    void setHorodatage(QDateTime horodatage);
};

#endif // MESURES_H
