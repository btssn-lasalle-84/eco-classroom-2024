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

  private:
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

  signals:
};

#endif // SALLEECO_H
