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

QString SalleEco::getIndiceCO2(int indiceCO2)
{
    QStringList designations;
    designations << "Inconnu"
                 << "Excellente"
                 << "Très bien"
                 << "Modéré"
                 << "Mauvais"
                 << "Très mauvais"
                 << "Sévère";
    if(indiceCO2 >= 0 && indiceCO2 < IndiceQualiteAir::NbIndicesQualiteAir)
        return designations[indiceCO2];
    return QString();
}

QString SalleEco::getIndiceConfinement(int indiceConfinement)
{
    QStringList designations;
    designations << "Nul"
                 << "Faible"
                 << "Moyen"
                 << "Élevé"
                 << "Très Élevé"
                 << "Extrême";
    if(indiceConfinement >= 0 && indiceConfinement < IndiceConfinement::NbIndicesConfinement)
        return designations[indiceConfinement];
    return QString();
}

QString SalleEco::getIndiceIADI(int indiceIADI)
{
    QStringList designations;
    designations << "Aucun"
                 << "Gêne"
                 << "Mal-être"
                 << "Inconfort"
                 << "Stress intense"
                 << "Urgence médicale";
    if(indiceIADI >= 0 && indiceIADI < IndiceInconfortIADI::NbIndicesIADI)
        return designations[indiceIADI];
    return QString();
}

QString SalleEco::getIndiceTHI(int indiceTHI)
{
    QStringList designations;
    designations << "Inconnu"
                 << "Froid"
                 << "Frais"
                 << "Légèrement frais"
                 << "Neutre"
                 << "Légèrement tiède"
                 << "Tiède"
                 << "Chaud";

    int decalageIndiceTHI = indiceTHI + 4;

    if(indiceTHI >= IndiceTHI::InconnuTHI && indiceTHI < IndiceTHI::NbIndicesTHI)
        return designations[decalageIndiceTHI];
    return QString();
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

    qDebug() << Q_FUNC_INFO << "indiceCO2" << indiceCO2 << SalleEco::getIndiceCO2(indiceCO2);

    if(indiceCO2 != indiceCO2Precedent)
    {
        emit nouvelIndiceQualiteAir(nom, SalleEco::getIndiceCO2(indiceCO2));
    }
}

int SalleEco::calculProportionBasse()
{
    int valeurProportionBasse = 0;

    for(const MesureCO2& mesure: mesuresCO2)
    {
        if((mesure.co2 >= PROPORTION_VALEUR_BASSE) && (mesure.co2 <= PROPORTION_VALEUR_HAUTE))
        {
            valeurProportionBasse++;
        }
    }
    return valeurProportionBasse;
}

int SalleEco::calculProportionHaute()
{
    int valeurProportionHaute = 0;

    for(const MesureCO2& mesure: mesuresCO2)
    {
        if(mesure.co2 >= PROPORTION_VALEUR_HAUTE)
        {
            valeurProportionHaute++;
        }
    }
    return valeurProportionHaute;
}

void SalleEco::determinerIndiceConfinement()
{
    int indiceConfinementPrecedent = indiceConfinement;

    if(mesuresCO2.size() > 1)
    {
        int    n0 = 0; // nombre de valeurs inférieures ou égales à 1000 ppm (n0)
        int    n1 = 0; // nombre de valeurs comprises entre 1000 et 1700 ppm inclus (n1)
        int    n2 = 0; // nombre de valeurs supérieures à 1700 ppm (n2)
        double f1 = 0.;
        double f2 = 0.;

        n1 =
          calculProportionBasse(); // nombre de valeurs comprises entre 1000 et 1700 ppm inclus (n1)
        n2 = calculProportionHaute(); // nombre de valeurs supérieures à 1700 ppm (n2)
        n0 = mesuresCO2.size() - n1 - n2;

        // Division par zéro ?
        if((n0 + n1 + n2) == 0)
            return;

        f1 = (double)n1 / (double)(n0 + n1 + n2);
        f2 = (double)n2 / (double)(n0 + n1 + n2);

        qDebug() << Q_FUNC_INFO << "n0" << n0 << "n1" << n1 << "n2" << n2;
        double calculIcone = (2.5 / log(2.)) * log(1. + f1 + 3. * f2);
        qDebug() << Q_FUNC_INFO << "calculIcone" << calculIcone;

        if(calculIcone < SEUIL_ICONE_NUL)
        {
            indiceConfinement = IndiceConfinement::Nul;
        }
        else if((calculIcone >= SEUIL_ICONE_NUL) && calculIcone < SEUIL_ICONE_FAIBLE)
        {
            indiceConfinement = IndiceConfinement::Faible;
        }
        else if((calculIcone >= SEUIL_ICONE_FAIBLE) && calculIcone < SEUIL_ICONE_MOYEN)
        {
            indiceConfinement = IndiceConfinement::Moyen;
        }
        else if((calculIcone >= SEUIL_ICONE_MOYEN) && calculIcone < SEUIL_ICONE_ELEVE)
        {
            indiceConfinement = IndiceConfinement::Eleve;
        }
        else if((calculIcone >= SEUIL_ICONE_ELEVE) && calculIcone < SEUIL_ICONE_TRES_ELEVE)
        {
            indiceConfinement = IndiceConfinement::TresEleve;
        }
        else if(calculIcone >= SEUIL_ICONE_TRES_ELEVE)
        {
            indiceConfinement = IndiceConfinement::Extreme;
        }
    }
    else
    {
        MesureCO2 mesureCO2 = getMesureCO2();
        qDebug() << Q_FUNC_INFO << "mesureCO2" << mesureCO2.co2;

        if(mesureCO2.co2 >= SEUIL_MAX_CO2_CLASSE)
        {
            indiceConfinement = IndiceConfinement::Eleve;
        }
        else
        {
            indiceConfinement = IndiceConfinement::Nul;
        }
    }
    qDebug() << Q_FUNC_INFO << "indiceConfinement" << indiceConfinement
             << SalleEco::getIndiceConfinement(indiceConfinement);

    if(indiceConfinement != indiceConfinementPrecedent)
    {
        emit nouvelIndiceConfinement(nom, SalleEco::getIndiceConfinement(indiceConfinement));
    }
}

void SalleEco::determinerIndiceIADI()
{
    int indiceIADIPrecedent = indiceIADI;
    // L’indice de confort thermique IADI (Indoor Air Disconfort Index) se calcule (Moschandreas
    // et Sofuoglu, 2004) à partir de la température de l’air intérieur et l’humidité relative
    qDebug() << Q_FUNC_INFO << "temperature" << getTemperature().temperature << "humidite"
             << getHumidite().humidite;
    double iadi = getTemperature().temperature - 0.55 * (1 - 0.01 * getHumidite().humidite) *
                                                   (getTemperature().temperature - 14.5);
    qDebug() << Q_FUNC_INFO << "iadi" << iadi;

    if(iadi < SEUIL_INCONFORT_IADI_AUCUN)
    {
        indiceIADI = IndiceInconfortIADI::Aucun;
    }
    else if(iadi >= SEUIL_INCONFORT_IADI_AUCUN && iadi < SEUIL_INCONFORT_IADI_GENE)
    {
        indiceIADI = IndiceInconfortIADI::Gene;
    }
    else if(iadi >= SEUIL_INCONFORT_IADI_GENE && iadi < SEUIL_INCONFORT_IADI_MAL_ETRE)
    {
        indiceIADI = IndiceInconfortIADI::MalEtre;
    }
    else if(iadi >= SEUIL_INCONFORT_IADI_MAL_ETRE && iadi < SEUIL_INCONFORT_IADI_INCONFORT)
    {
        indiceIADI = IndiceInconfortIADI::Inconfort;
    }
    else if(iadi >= SEUIL_INCONFORT_IADI_INCONFORT && iadi < SEUIL_INCONFORT_IADI_STRESS_INTENSE)
    {
        indiceIADI = IndiceInconfortIADI::StressIntense;
    }
    else if(iadi >= SEUIL_INCONFORT_IADI_STRESS_INTENSE)
    {
        indiceIADI = IndiceInconfortIADI::UrgenceMedicale;
    }

    qDebug() << Q_FUNC_INFO << "indiceIADI" << indiceIADI << SalleEco::getIndiceIADI(indiceIADI);

    if(indiceIADI != indiceIADIPrecedent)
    {
        emit nouvelIndiceIADI(nom, SalleEco::getIndiceIADI(indiceIADI));
    }
}

void SalleEco::determinerIndiceTHI()
{
    int indiceTHIPrecedent = indiceTHI;
    // L’indice THI (Temperature Humidity Index) de Thom se calcule selon la formule suivante :

    qDebug() << Q_FUNC_INFO << "temperature" << getTemperature().temperature << "humidite"
             << getHumidite().humidite;
    double calculDeThom = getTemperature().temperature - ((0.55 - 0.0055 * getHumidite().humidite) *
                                                          (getTemperature().temperature - 14.5));
    qDebug() << Q_FUNC_INFO << "calculDeThom" << calculDeThom;

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

    qDebug() << Q_FUNC_INFO << "indiceTHI" << indiceTHI << SalleEco::getIndiceTHI(indiceTHI);

    if(indiceTHI != indiceTHIPrecedent)
    {
        emit nouvelIndiceTHI(nom, SalleEco::getIndiceTHI(indiceTHI));
    }
}
