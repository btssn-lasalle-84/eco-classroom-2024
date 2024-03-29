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
};

#endif // MESURES_H
