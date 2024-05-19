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
#include <QMap>
#include <QString>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM "EcoClassroom"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION "0.2"

class SalleEco;
class BaseDeDonnees;
class DialogueMQTT;

/**
 * @class IHMEcoClassroom
 * @brief Déclaration de la classe IHMEcoClassroom
 * @details Cette classe gère l'IHM
 */
class IHMEcoClassroom : public QWidget
{
    Q_OBJECT

  private:
    QMap<QString, SalleEco*> salles;        //!< Les salles
    BaseDeDonnees*           baseDeDonnees; //!< l'association vers la classe BaseDeDonnees
    DialogueMQTT*            dialogueMQTT;  //!< l'association vers la classe DialogueMQTT
    // Widgets
    QTableWidget* tableauSallesEco;

    void gererEvenements();
    void creerTableauSallesEco();
    void ajouterSalleEcoTableau(const SalleEco& salle);
    void afficherSallesEco();

    /**
     * @enum ColonneTableauSallesEco
     * @brief Définit les différentes colonne du tableau tableauSallesEco
     */
    enum ColonneTableauSallesEco
    {
        COLONNE_SALLE_NOM,               //!< Le nom de la salle
        COLONNE_SALLE_DISPONIBILITE,     //!< La disponibilité de la salle
        COLONNE_SALLE_QUALITE_AIR,       //!< La qualité de l'air
        COLONNE_SALLE_CONFORT_THERMIQUE, //!< Le confort thermique
        COLONNE_SALLE_FENETRES,          //!< L'état des fenétres
        COLONNE_SALLE_LUMIERES,          //!< L'état des lumières
        NB_COLONNES_TABLEAU
    };

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  signals:

  public slots:
    void recupererSalles();
    void afficherIndiceQualiteAir(QString, QString);
    void afficherConfortThermique(QString , QString );

};

#endif // IHMECOCLASSROOM_H
