#include "salleeco.h"
#include "indices.h"
#include "basededonnees.h"
#include <QDebug>

SalleEco::SalleEco(QObject* parent) : QObject(parent), baseDeDonnees(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();
}

SalleEco::SalleEco(QString  idSalle,
                   QString  nom,
                   QString  description,
                   double   superficie,
                   QObject* parent) :
    QObject(parent),
    idSalle(idSalle), nom(nom), description(description), superficie(superficie),
    baseDeDonnees(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO << idSalle << nom << description << superficie;
    baseDeDonnees->connecter();
}

SalleEco::~SalleEco()
{
    BaseDeDonnees::detruireInstance();
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

void SalleEco::traiterNouvelleDonnee(QString nomSalleEco, QString typeDonnee, QString donnee)
{
    // est-ce une donnée pour ma salle ?
    if(nomSalleEco == nom)
    {
        qDebug() << Q_FUNC_INFO << "nom" << nom << QDateTime::currentDateTime().toString()
                 << "nomSalleEco" << nomSalleEco << "typeDonnee" << typeDonnee << "donnee"
                 << donnee;

        QString requete;

        if(typeDonnee == "co2")
        {
            ajouterMesureCO2(donnee.toInt());

            requete = "INSERT INTO MesureCo2 (idSalle,co2,horodatage) VALUES (" + idSalle + "," +
                      donnee + ",NOW())";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
            determinerIndiceQualiteAir();
            determinerIndiceConfinement();

            // @todo Si changement d'indice, signaler nouvelIndiceQualiteAir(nom) et/ou
            // nouvelIndiceConfinement(nom)
        }
        else if(typeDonnee == "temperature")
        {
            ajouterMesureTemperature(donnee.toDouble());

            requete = "INSERT INTO MesureTemperature (idSalle,temperature,horodatage) VALUES (" +
                      idSalle + "," + donnee + ",NOW())";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
            determinerIndiceTHI();
            determinerIndiceIADI();
        }
        else if(typeDonnee == "humidite")
        {
            ajouterMesureHumidite(donnee.toInt());

            requete = "INSERT INTO MesureHumidite (idSalle,humidite,horodatage) VALUES (" +
                      idSalle + "," + donnee + ",NOW())";
            qDebug() << Q_FUNC_INFO << "requete" << requete;
            baseDeDonnees->executer(requete);
            determinerIndiceTHI();
            determinerIndiceIADI();
        }
    }
}

void SalleEco::determinerIndiceQualiteAir()
{
    MesureCO2 mesureCO2 = getMesureCO2();
    qDebug() << Q_FUNC_INFO << "mesureCO2" << mesureCO2.co2;

    int indiceCO2Precedent = indiceCO2;

    if(mesureCO2.co2 >= SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MINIMUM &&
       mesureCO2.co2 <= SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MAXIMUM)
    {
        indiceCO2 = IndiceQualiteAir::Excellente;
    }
    else if(mesureCO2.co2 >= SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MINIMUM &&
            mesureCO2.co2 <= SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MAXIMUM)
    {
        indiceCO2 = IndiceQualiteAir::TresBien;
    }
    else if(mesureCO2.co2 >= SEUIL_QUALITE_AIR_MODERE_NIVEAU_MINIMUM &&
            mesureCO2.co2 <= SEUIL_QUALITE_AIR_MODERE_NIVEAU_MAXIMUM)
    {
        indiceCO2 = IndiceQualiteAir::Modere;
    }
    else if(mesureCO2.co2 >= SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MINIMUM &&
            mesureCO2.co2 <= SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MAXIMUM)
    {
        indiceCO2 = IndiceQualiteAir::Mauvais;
    }
    else if(mesureCO2.co2 >= SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MINIMUM &&
            mesureCO2.co2 <= SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MAXIMUM)
    {
        indiceCO2 = IndiceQualiteAir::TresMauvais;
    }
    else
    {
        indiceCO2 = IndiceQualiteAir::Severe;
    }

    if(indiceCO2 != indiceCO2Precedent)
    {
        emit nouvelIndiceQualiteAir(nom);
    }
    qDebug() << Q_FUNC_INFO << "indiceCO2" << indiceCO2;
}

void SalleEco::determinerIndiceConfinement()
{
    int indiceConfinementPrecedent = indiceConfinement;

    qDebug() << Q_FUNC_INFO << "indiceConfinement" << indiceConfinement;

    if(indiceConfinement != indiceConfinementPrecedent)
    {
        emit nouvelIndiceConfinement(nom);
    }
}

void SalleEco::determinerIndiceIADI()
{
    double indiceIADI = getTemperature().temperature - 0.55 * (1 - 0.01 * getHumidite().humidite) *
                                                         (getTemperature().temperature - 14.5);

    int indiceIADIPrecedent = indiceIADI;

    qDebug() << Q_FUNC_INFO << "indiceIADI" << indiceIADI;

    if(indiceIADI != indiceIADIPrecedent)
    {
        emit nouvelIndiceIADI(nom);
    }
}

void SalleEco::determinerIndiceTHI()
{
    double calculDeThom = getTemperature().temperature - 0.55 *
                                                           (1 - 0.01 * getHumidite().humidite) *
                                                           (getTemperature().temperature - 14.5);
    qDebug() << Q_FUNC_INFO << "calculDeThom" << calculDeThom;

    int indiceTHIPrecedent = indiceTHI;

    if(calculDeThom < SEUIL_CONFORT_THI_FROID)
    {
        indiceTHI = INDICE_CONFORT_THI_FROID;
    }
    else if(calculDeThom >= SEUIL_CONFORT_THI_FROID && calculDeThom < SEUIL_CONFORT_THI_FRAIS)
    {
        indiceTHI = INDICE_CONFORT_THI_FRAIS;
    }
    else if(calculDeThom >= SEUIL_CONFORT_THI_FRAIS &&
            calculDeThom < SEUIL_CONFORT_THI_LEGEREMENT_FRAIS)
    {
        indiceTHI = INDICE_CONFORT_THI_LEGEREMENT_FRAIS;
    }
    else if(calculDeThom >= SEUIL_CONFORT_THI_LEGEREMENT_FRAIS &&
            calculDeThom < SEUIL_CONFORT_THI_NEUTRE)
    {
        indiceTHI = INDICE_CONFORT_THI_NEUTRE;
    }
    else if(calculDeThom >= SEUIL_CONFORT_THI_NEUTRE &&
            calculDeThom < SEUIL_CONFORT_THI_LEGEREMENT_TIEDE)
    {
        indiceTHI = INDICE_CONFORT_THI_LEGEREMENT_TIEDE;
    }
    else if(calculDeThom >= SEUIL_CONFORT_THI_LEGEREMENT_TIEDE &&
            calculDeThom < SEUIL_CONFORT_THI_TIEDE)
    {
        indiceTHI = INDICE_CONFORT_THI_TIEDE;
    }
    else
    {
        indiceTHI = INDICE_CONFORT_THI_CHAUD;
    }

    qDebug() << Q_FUNC_INFO << "indiceTHI" << indiceTHI;

    if(indiceTHI != indiceTHIPrecedent)
    {
        emit nouvelIndiceTHI(nom);
    }
}
