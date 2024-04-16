#include "salleeco.h"
#include "indices.h"
#include <QDebug>

SalleEco::SalleEco(QObject* parent) : QObject(parent)
{
}

SalleEco::SalleEco(QString  idSalle,
                   QString  nom,
                   QString  description,
                   double   superficie,
                   QObject* parent) :
    QObject(parent),
    idSalle(idSalle), nom(nom), description(description), superficie(superficie)
{
    qDebug() << Q_FUNC_INFO << idSalle << nom << description << superficie;
}

SalleEco::~SalleEco()
{
    qDebug() << Q_FUNC_INFO << idSalle << nom << description << superficie;
}

QString SalleEco::getIdSalle() const
{
    return idSalle;
}

QString SalleEco::getNom() const
{
    return nom;
}

QString SalleEco::getDescription() const
{
    return description;
}

double SalleEco::getSuperficie() const
{
    return superficie;
}

int SalleEco::getIndiceCO2() const
{
    return indiceCO2;
}

int SalleEco::getIndiceIADI() const
{
    return indiceIADI;
}

int SalleEco::getIndiceTHI() const
{
    return indiceTHI;
}

int SalleEco::getIndiceConfinement() const
{
    return indiceConfinement;
}

MesureCO2 SalleEco::getMesureCO2() const
{
    if(!mesuresCO2.isEmpty())
    {
        return mesuresCO2.last();
    }
    return MesureCO2();
}

MesureTemperature SalleEco::getTemperature() const
{
    if(!mesuresTemperature.isEmpty())
    {
        return mesuresTemperature.last();
    }
    return MesureTemperature();
}

MesureHumidite SalleEco::getHumidite() const
{
    if(!mesuresHumidite.isEmpty())
    {
        return mesuresHumidite.last();
    }
    return MesureHumidite();
}

EtatPresence SalleEco::getEtatPresence() const
{
    if(!etatsPresence.isEmpty())
    {
        return etatsPresence.last();
    }
    return EtatPresence();
}

EtatFenetres SalleEco::getEtatFenetres() const
{
    if(!etatsFenetres.isEmpty())
    {
        return etatsFenetres.last();
    }
    return EtatFenetres();
}

EtatLumieres SalleEco::getEtatLumieres() const
{
    if(!etatsLumieres.isEmpty())
    {
        return etatsLumieres.last();
    }
    return EtatLumieres();
}

void SalleEco::setIDSalle(QString idSalle)
{
    this->idSalle = idSalle;
}

void SalleEco::setNom(QString nom)
{
    this->nom = nom;
}

void SalleEco::setDescription(QString description)
{
    this->description = description;
}

void SalleEco::setSuperficie(double superficie)
{
    this->superficie = superficie;
}

void SalleEco::setIndiceCO2(int indiceCO2)
{
    this->indiceCO2 = indiceCO2;
}

void SalleEco::setIndiceIADI(int indiceIADI)
{
    this->indiceIADI = indiceIADI;
}

void SalleEco::setIndiceTHI(int indiceTHI)
{
    this->indiceTHI = indiceTHI;
}

void SalleEco::setIndiceConfinement(int indiceConfinement)
{
    this->indiceConfinement = indiceConfinement;
}

void SalleEco::ajouterMesureCO2(int co2)
{
    MesureCO2 mesureCO2;
    mesureCO2.co2        = co2;
    mesureCO2.horodatage = QDateTime::currentDateTime();
    mesureCO2.valide     = true;
    mesuresCO2.push_back(mesureCO2);
}

void SalleEco::ajouterMesureTemperature(double temperature)
{
    MesureTemperature mesureTemperature;
    mesureTemperature.temperature = temperature;
    mesureTemperature.horodatage  = QDateTime::currentDateTime();
    mesureTemperature.valide      = true;
    mesuresTemperature.push_back(mesureTemperature);
}

void SalleEco::ajouterMesureHumidite(int humidite)
{
    MesureHumidite mesureHumidite;
    mesureHumidite.humidite   = humidite;
    mesureHumidite.horodatage = QDateTime::currentDateTime();
    mesureHumidite.valide     = true;
    mesuresHumidite.push_back(mesureHumidite);
}

void SalleEco::ajouterEtatPresence(bool presence)
{
    EtatPresence etatPresence;
    etatPresence.presence   = presence;
    etatPresence.horodatage = QDateTime::currentDateTime();
    etatPresence.valide     = true;
    etatsPresence.push_back(etatPresence);
}

void SalleEco::ajouterEtatFenetres(bool fenetres)
{
    EtatFenetres etatFenetres;
    etatFenetres.fenetres   = fenetres;
    etatFenetres.horodatage = QDateTime::currentDateTime();
    etatFenetres.valide     = true;
    etatsFenetres.push_back(etatFenetres);
}

void SalleEco::ajouterEtatLumieres(bool lumieres)
{
    EtatLumieres etatLumieres;
    etatLumieres.lumieres   = lumieres;
    etatLumieres.horodatage = QDateTime::currentDateTime();
    etatLumieres.valide     = true;
    etatsLumieres.push_back(etatLumieres);
}

void SalleEco::determinerIndiceQualiteAir()
{
    int mesuresCO2 = getIndiceCO2();

    if(mesuresCO2 >= SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MINIMUM &&
       mesuresCO2 <= SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MAXIMUM)
    {
        mesuresCO2 = IndiceQualiteAir::Excellente;
    }
    else if(mesuresCO2 >= SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MINIMUM &&
            mesuresCO2 <= SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MAXIMUM)
    {
        mesuresCO2 = IndiceQualiteAir::TresBien;
    }
    else if(mesuresCO2 >= SEUIL_QUALITE_AIR_MODERE_NIVEAU_MINIMUM &&
            mesuresCO2 <= SEUIL_QUALITE_AIR_MODERE_NIVEAU_MAXIMUM)
    {
        mesuresCO2 = IndiceQualiteAir::Modere;
    }
    else if(mesuresCO2 >= SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MINIMUM &&
            mesuresCO2 <= SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MAXIMUM)
    {
        mesuresCO2 = IndiceQualiteAir::Mauvais;
    }
    else if(mesuresCO2 >= SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MINIMUM &&
            mesuresCO2 <= SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MAXIMUM)
    {
        mesuresCO2 = IndiceQualiteAir::TresMauvais;
    }
    else
    {
        mesuresCO2 = IndiceQualiteAir::Severe;
    }
}
