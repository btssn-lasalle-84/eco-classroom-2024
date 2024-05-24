#ifndef ETATS_H
#define ETATS_H

#include <QDateTime>

struct EtatPresence
{
    bool      presence;
    QDateTime horodatage;
    bool      valide = false;
};

struct EtatFenetres
{
    bool      fenetres;
    QDateTime horodatage;
    bool      valide = false;
};

struct EtatLumieres
{
    bool      lumieres;
    QDateTime horodatage;
    bool      valide = false;
};

#endif // ETATS_H
