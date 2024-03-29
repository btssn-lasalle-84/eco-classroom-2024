#ifndef ETATS_H
#define ETATS_H

#include <QDateTime>

class Etats
{
  private:
    bool      presence;
    bool      fenetres;
    bool      lumieres;
    QDateTime horodatage;

  public:
    Etats();
    ~Etats();
};

#endif // ETATS_H
