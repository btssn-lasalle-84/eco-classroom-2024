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
    int               indiceCo2;
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

  signals:
};

#endif // SALLEECO_H
