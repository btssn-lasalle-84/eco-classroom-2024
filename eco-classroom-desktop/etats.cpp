#include "etats.h"
#include <QDebug>

Etats::Etats() :
    presence(false), fenetres(false), lumieres(false), horodatage(QDateTime::currentDateTime())
{
    qDebug() << Q_FUNC_INFO << "horodatage" << horodatage.toString("hh:mm:ss");
}

Etats::~Etats()
{
    qDebug() << Q_FUNC_INFO;
}
