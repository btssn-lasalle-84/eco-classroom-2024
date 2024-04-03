#ifndef ECOCLASSROOM_H
#define ECOCLASSROOM_H

#include <QObject>
#include <QString>

class EcoClassroom : public QObject
{
    Q_OBJECT

  private:
    double  indiceHumidite;
    double  indiceCo2;
    double  indiceConfort;
    QString description;
    QString nom;
    double  superficie;

  public:
    explicit EcoClassroom(QObject* parent = nullptr);

  signals:
};

#endif // ECOCLASSROOM_H
