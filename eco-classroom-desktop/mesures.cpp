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
