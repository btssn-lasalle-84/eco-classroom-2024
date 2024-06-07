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
  public:
    /**
     * @enum Filtrage
     * @brief Les différentes filtrages
     */
    enum Filtrage
    {
        Toutes,
        Disponibles,
        Interventions,
        NbFiltres
    };

  private:
    QMap<QString, SalleEco*> salles;        //!< Les salles
    BaseDeDonnees*           baseDeDonnees; //!< l'association vers la classe BaseDeDonnees
    DialogueMQTT*            dialogueMQTT;  //!< l'association vers la classe DialogueMQTT
    Filtrage                 filtrageCourant;
    // Widgets
    QVBoxLayout*  layoutPrincipal;
    QVBoxLayout*  layoutVueGenerale;
    QHBoxLayout*  layoutVueFiltrage;
    QHBoxLayout*  layoutVueTableau;
    QVBoxLayout*  layoutVueSpecifique;
    QHBoxLayout*  layoutVueInformations;
    QHBoxLayout*  layoutVueDescription;
    QHBoxLayout*  layoutVueDonnees;
    QVBoxLayout*  layoutVueGauche;
    QVBoxLayout*  layoutVueCentrale;
    QVBoxLayout*  layoutVueDroite;
    QComboBox*    choixFiltrage;
    QTableWidget* tableauSallesEco;
    QFrame*       cadreSalleSpecifique;
    QLabel*       nomSalle;
    QLabel*       superficieSalle;
    QLabel*       descriptionSalle;
    QLabel*       co2Salle;
    QLabel*       temperatureSalle;
    QLabel*       humiditeSalle;
    QLabel*       presenceSalle;
    QLabel*       lumieresSalle;
    QLabel*       fenetresSalle;
    QLabel*       qualiteAirSalle;
    QLabel*       confortSalle;
    QLabel*       alertesSalle;

    void creerFenetrePrincipale();
    void creerStructureFenetrePrincipale();
    void creerSelectionFiltrage();
    void creerTableauSallesEco();
    void creerSalleSpecifique();
    void positionnerElementsFenetrePrincipale();
    void gererEvenements();

    void ajouterSalleEcoTableau(const SalleEco& salle);
    void afficherSallesEco();
    void afficherSalleSpecifique(SalleEco* salleEco);
    void effacerTableauSallesEco();

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
        COLONNE_SALLE_INTERVENTIONS,
        NB_COLONNES_TABLEAU
    };

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  signals:

  public slots:
    void recupererSalles();
    void afficherIndiceQualiteAir(QString, QString);
    void afficherIndiceTHI(QString, QString);
    void afficherEtatFenetre(QString nomSalleEco, QString etat);
    void afficherEtatLumiere(QString nomSalleEco, QString etat);
    void afficherEtatPresence(QString nomSalleEco, QString etat);
    void afficherIntervention(QString nomSalleEco, QString intervention);
    void afficherNouvelleDonnee(QString nomSalleEco, QString typeDonnee, QString donnee);
    void selectionnerSalleSpecifique(int ligne, int colonne);
    void selectionnerFiltrage(int indexFiltrage);
};

#endif // IHMECOCLASSROOM_H
