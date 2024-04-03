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
