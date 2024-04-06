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
