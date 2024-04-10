#include "etats.h"
#include <QDebug>

Etats::Etats() :
    presence(false), fenetres(false), lumieres(false), horodatage(QDateTime::currentDateTime())
{
    qDebug() << Q_FUNC_INFO << "horodatage" << horodatage.toString("hh:mm:ss");
}

Etats::Etats(bool presence, bool fenetres, bool lumieres, QDateTime horodatage) :
presence(presence, lumieres(lumieres), fenetres(fenetres), horodatage(horodatage)
{
    qDebug() << Q_FUNC_INFO;

}

Etats::~Etats()
{
    qDebug() << Q_FUNC_INFO;
}

bool Etats::getPresence() const
{
    return presence;
}

bool Etats::getFenetres() const
{
    return fenetres;
}

bool Etats::getLumieres() const
{
    return lumieres;
}

QDateTime Etats::getHorodatage() const
{
    return horodatage;
}

void Etats::setPresence(bool presence)
{
    this->presence = presence;
}

void Etats::setFenetres(bool fenetres)
{
    this->fenetres = fenetres;
}

void Etats::setLumieres(bool lumieres)
{
    this->lumieres = lumieres;
}

void Etats::setHorodatage(QDateTime horodatage)
{
    this->horodatage = horodatage;
}
