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
    Etats(bool presence, bool fenetres, bool lumieres, QDateTime horodatage);
    ~Etats();

    bool      getPresence() const;
    bool      getFenetres() const;
    bool      getLumieres() const;
    QDateTime getHorodatage() const;

    void setPresence(bool presence);
    void setFenetres(bool fenetres);
    void setLumieres(bool lumieres);
    void setHorodatage(QDateTime horodatage);
};

#endif // ETATS_H
