#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 *
 * @brief Déclaration de la classe IHMEcoClassroom
 * @author Thomas VIGNAL
 * @version 0.1
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM "EcoClassroom"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION "0.1"

/**
 * @class IHMEcoClassroom
 * @brief Déclaration de la classe IHMEcoClassroom
 * @details Cette classe gère l'IHM
 */
class IHMEcoClassroom : public QWidget
{
    Q_OBJECT

  private:
  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  signals:

  public slots:
};

#endif // IHMECOCLASSROOM_H
