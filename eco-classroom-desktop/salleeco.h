#ifndef SALLEECO_H
#define SALLEECO_H

#include <QObject>
#include <QString>
#include <QVector>

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
