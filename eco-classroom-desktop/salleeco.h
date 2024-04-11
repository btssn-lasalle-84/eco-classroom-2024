#ifndef SALLEECO_H
#define SALLEECO_H

#include <QObject>
#include <QString>
#include <QVector>

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

class Mesures;
class Etats;

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
    QString           idSalle;
    QString           nom;
    QString           description;
    double            superficie;
    int               indiceCO2;
    int               indiceIADI;
    int               indiceTHI;
    int               indiceConfinement;
    QVector<Mesures*> mesures;
    QVector<Etats*>   etats;

  public:
    explicit SalleEco(QObject* parent = nullptr);
    explicit SalleEco(QString  idSalle,
                      QString  nom,
                      QString  description,
                      double   superficie,
                      QObject* parent = nullptr);
    ~SalleEco();

    QString getIdSalle() const;
    QString getNom() const;
    QString getDescription() const;
    double  getSuperficie() const;
    int     getIndiceCO2() const;
    int     getIndiceIADI() const;
    int     getIndiceTHI() const;
    int     getIndiceConfinement() const;

    void setIDSalle(QString idSalle);
    void setNom(QString nom);
    void setDescription(QString description);
    void setSuperficie(double superficie);
    void setIndiceCO2(int indiceCO2);
    void setIndiceIADI(int indiceIADI);
    void setIndiceTHI(int indiceTHI);
    void setIndiceConfinement(int indiceConfinement);

    // @todo ajouter accesseurs/mutateurs get/set pour les mesures et les états

  signals:
};

#endif // SALLEECO_H
