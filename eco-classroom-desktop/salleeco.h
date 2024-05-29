#ifndef SALLEECO_H
#define SALLEECO_H

#include <QObject>
#include <QString>
#include <QVector>

#include "mesures.h"
#include "etats.h"

#define SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MINIMUM    0
#define SEUIL_QUALITE_AIR_EXCELLENT_NIVEAU_MAXIMUM    400
#define SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MINIMUM    401
#define SEUIL_QUALITE_AIR_TRES_BIEN_NIVEAU_MAXIMUM    1000
#define SEUIL_QUALITE_AIR_MODERE_NIVEAU_MINIMUM       1001
#define SEUIL_QUALITE_AIR_MODERE_NIVEAU_MAXIMUM       1500
#define SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MINIMUM      1501
#define SEUIL_QUALITE_AIR_MAUVAIS_NIVEAU_MAXIMUM      2000
#define SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MINIMUM 2001
#define SEUIL_QUALITE_AIR_TRES_MAUVAIS_NIVEAU_MAXIMUM 5000
#define SEUIL_QUALITE_AIR_SEVERE                      5001

#define SEUIL_MAX_CO2_CLASSE 1300

#define PROPORTION_VALEUR_BASSE 1000
#define PROPORTION_VALEUR_HAUTE 1700

#define INDICE_CONFINEMENT_NUL        0
#define INDICE_CONFINEMENT_FAIBLE     1
#define INDICE_CONFINEMENT_MOYEN      2
#define INDICE_CONFINEMENT_ELEVE      3
#define INDICE_CONFINEMENT_TRES_ELEVE 4
#define INDICE_CONFINEMENT_EXTREME    5

#define SEUIL_CONFORT_THI_FROID            -1.7
#define SEUIL_CONFORT_THI_FRAIS            13.
#define SEUIL_CONFORT_THI_LEGEREMENT_FRAIS 15.
#define SEUIL_CONFORT_THI_NEUTRE           20.
#define SEUIL_CONFORT_THI_LEGEREMENT_TIEDE 26.5
#define SEUIL_CONFORT_THI_TIEDE            30.

#define INDICE_CONFORT_THI_FROID            -3
#define INDICE_CONFORT_THI_FRAIS            -2
#define INDICE_CONFORT_THI_LEGEREMENT_FRAIS -1
#define INDICE_CONFORT_THI_NEUTRE           0
#define INDICE_CONFORT_THI_LEGEREMENT_TIEDE 1
#define INDICE_CONFORT_THI_TIEDE            2
#define INDICE_CONFORT_THI_CHAUD            3

#define SEUIL_INCONFORT_IADI_AUCUN          20
#define SEUIL_INCONFORT_IADI_GENE           24
#define SEUIL_INCONFORT_IADI_MAL_ETRE       27
#define SEUIL_INCONFORT_IADI_INCONFORT      29
#define SEUIL_INCONFORT_IADI_STRESS_INTENSE 32

#define SEUIL_ICONE_NUL        0.5
#define SEUIL_ICONE_FAIBLE     1.5
#define SEUIL_ICONE_MOYEN      2.5
#define SEUIL_ICONE_ELEVE      3.5
#define SEUIL_ICONE_TRES_ELEVE 4.5

class BaseDeDonnees;

class SalleEco : public QObject
{
    Q_OBJECT

  public:
    /**
     * @enum TableSalle
     * @brief Les différents champs de la table Salle
     */
    enum TableSalle
    {
        CHAMP_IDSALLE = 0,
        CHAMP_NOM,
        CHAMP_DESCRIPTION,
        CHAMP_SUPERFICIE
        // @todo à complèter
    };

  private:
    QString                    idSalle;
    QString                    nom;
    QString                    description;
    double                     superficie;
    int                        indiceCO2;
    int                        indiceIADI;
    int                        indiceTHI;
    int                        indiceConfinement;
    QVector<MesureCO2>         mesuresCO2;
    QVector<MesureTemperature> mesuresTemperature;
    QVector<MesureHumidite>    mesuresHumidite;
    QVector<EtatPresence>      etatsPresence;
    QVector<EtatFenetres>      etatsFenetres;
    QVector<EtatLumieres>      etatsLumieres;
    BaseDeDonnees*             baseDeDonnees; //!< l'association vers la classe BaseDeDonnees

    void determinerIndiceQualiteAir();
    int  calculProportionBasse();
    int  calculProportionHaute();
    void determinerIndiceConfinement();
    void determinerIndiceIADI();
    void determinerIndiceTHI();

  public:
    explicit SalleEco(QObject* parent = nullptr);
    explicit SalleEco(QString  idSalle,
                      QString  nom,
                      QString  description,
                      double   superficie,
                      QObject* parent = nullptr);
    ~SalleEco();

    QString           getIdSalle() const;
    QString           getNom() const;
    QString           getDescription() const;
    double            getSuperficie() const;
    int               getIndiceCO2() const;
    int               getIndiceIADI() const;
    int               getIndiceTHI() const;
    int               getIndiceConfinement() const;
    MesureCO2         getMesureCO2() const;
    MesureTemperature getTemperature() const;
    MesureHumidite    getHumidite() const;
    EtatPresence      getEtatPresence() const;
    EtatFenetres      getEtatFenetres() const;
    EtatLumieres      getEtatLumieres() const;

    void setIDSalle(QString idSalle);
    void setNom(QString nom);
    void setDescription(QString description);
    void setSuperficie(double superficie);
    void setIndiceCO2(int indiceCO2);
    void setIndiceIADI(int indiceIADI);
    void setIndiceTHI(int indiceTHI);
    void setIndiceConfinement(int indiceConfinement);
    void ajouterMesureCO2(int co2);
    void ajouterMesureTemperature(double temperature);
    void ajouterMesureHumidite(int humidite);
    void ajouterEtatPresence(bool presence);
    void ajouterEtatFenetres(bool fenetres);
    void ajouterEtatLumieres(bool lumieres);

    static QString getIndiceCO2(int indiceCO2);
    static QString getIndiceConfinement(int indiceConfinement);
    static QString getIndiceIADI(int indiceIADI);
    static QString getIndiceTHI(int indiceTHI);
    static QString getFenetres(const EtatFenetres& etatFenetre);
    static QString getLumieres(const EtatLumieres& etatLumiere);
    static QString getPresence(const EtatPresence& etatPresence);

  public slots:
    void traiterNouvelleDonnee(QString nomSalleEco, QString typeDonnee, QString donnee);

  signals:
    void nouvelIndiceQualiteAir(QString nomSalleEco, QString designationIndice);
    void nouvelIndiceConfinement(QString nomSalleEco, QString designationIndice);
    void nouvelIndiceIADI(QString nomSalleEco, QString designationIndice);
    void nouvelIndiceTHI(QString nomSalleEco, QString designationIndice);
    void nouvelEtatFenetre(QString nomSalleEco, QString etat);
    void nouvelEtatLumiere(QString nomSalleEco, QString etat);
    void nouvelEtatPresence(QString nomSalleEco, QString etat);
};

#endif // SALLEECO_H
