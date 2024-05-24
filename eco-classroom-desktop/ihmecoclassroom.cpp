#include "ihmecoclassroom.h"
#include "salleeco.h"
#include "basededonnees.h"
#include "dialoguemqtt.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 *
 * @brief Définition de la classe IHMEcoClassroom
 * @author Thomas VIGNAL
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::IHMEcoClassroom
 * @param parent L'adresse de l'objet parent, si nullptr IHMEcoClassroom sera la
 * fenêtre principale de l'application
 */
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QWidget(parent), baseDeDonnees(BaseDeDonnees::getInstance()),
    dialogueMQTT(new DialogueMQTT(this))
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();

    recupererSalles();
    creerTableauSallesEco();
    afficherSallesEco();

    gererEvenements();

    // showMaximized();
}

/**
 * @brief Destructeur de la classe IHMEcoClassroom
 */
IHMEcoClassroom::~IHMEcoClassroom()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

/**
 * @fn IHMEcoClassroom::recupererSalles
 * @brief Récupérer les salles depuis la base de données
 */
void IHMEcoClassroom::recupererSalles()
{
    qDebug() << Q_FUNC_INFO;
    salles.clear();

    QVector<QStringList> sallesBaseDeDonnees;
    QString              requete = "SELECT idSalle, nom, description, superficie FROM Salle";
    bool                 retour;

    retour = baseDeDonnees->recuperer(requete, sallesBaseDeDonnees);
    if(retour)
    {
        qDebug() << Q_FUNC_INFO << sallesBaseDeDonnees;
        for(int i = 0; i < sallesBaseDeDonnees.size(); ++i)
        {
            // qDebug() << Q_FUNC_INFO << sallesBaseDeDonnees[i];
            salles[sallesBaseDeDonnees[i][SalleEco::TableSalle::CHAMP_NOM]] = new SalleEco(
              sallesBaseDeDonnees[i][SalleEco::TableSalle::CHAMP_IDSALLE],
              sallesBaseDeDonnees[i][SalleEco::TableSalle::CHAMP_NOM],
              sallesBaseDeDonnees[i][SalleEco::TableSalle::CHAMP_DESCRIPTION],
              sallesBaseDeDonnees[i][SalleEco::TableSalle::CHAMP_SUPERFICIE].toDouble(),
              this);
        }
    }

    qDebug() << Q_FUNC_INFO << "salles" << salles;
}

void IHMEcoClassroom::afficherIndiceQualiteAir(QString nomSalleEco, QString designationIndice)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "designationIndice"
             << designationIndice;
    // recherche nomSalleEco dans le tableau des salles affichées
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementNom = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_QUALITE_AIR);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, designationIndice);
            return;
        }
    }
}

void IHMEcoClassroom::afficherIndiceTHI(QString nomSalleEco, QString designationIndice)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "designationIndice"
             << designationIndice;
    // recherche nomSalleEco dans le tableau des salles affichées
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementNom = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_CONFORT_THERMIQUE);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, designationIndice);
            return;
        }
    }
}

void IHMEcoClassroom::gererEvenements()
{
    QMapIterator<QString, SalleEco*> sallesEco(salles);
    while(sallesEco.hasNext())
    {
        sallesEco.next();
        connect(dialogueMQTT,
                SIGNAL(nouvelleDonnee(QString, QString, QString)),
                sallesEco.value(),
                SLOT(traiterNouvelleDonnee(QString, QString, QString)));
        connect(sallesEco.value(),
                SIGNAL(nouvelIndiceQualiteAir(QString, QString)),
                this,
                SLOT(afficherIndiceQualiteAir(QString, QString)));
        connect(sallesEco.value(),
                SIGNAL(nouvelIndiceTHI(QString, QString)),
                this,
                SLOT(afficherIndiceTHI(QString, QString)));
    }
    // @todo connecter le signal nouvelleDonnee(QString, QString, QString) vers un slot de l'IHM
    // pour afficher la nouvelle donnée
}

void IHMEcoClassroom::creerTableauSallesEco()
{
    QStringList labelsColonnes;
    labelsColonnes << "Salle"
                   << "Disponibilité"
                   << "Qualité d'air"
                   << "Confort Thermique"
                   << "Fenêtres"
                   << "Lumières"
                   << "Interventions";
    tableauSallesEco = new QTableWidget(this);

    // Personnalisation du QTableWidget
    tableauSallesEco->setColumnCount(labelsColonnes.count());
    tableauSallesEco->setHorizontalHeaderLabels(labelsColonnes);
    tableauSallesEco->setRowCount(0);
    // Cache la numérotation des lignes
    tableauSallesEco->verticalHeader()->setHidden(true);
    // Prend toute la largeur de la fenêtre
    tableauSallesEco->setMinimumWidth(width());
    // Largeur automatique des colonnes sur toute la largeur
    QHeaderView* headerView = tableauSallesEco->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    // Pas de scroll
    // tableauSallesEco->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // tableauSallesEco->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Positionnement du QTableWidget
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tableauSallesEco);
    setLayout(layout);
}

void IHMEcoClassroom::ajouterSalleEcoTableau(const SalleEco& salle)
{
    qDebug() << Q_FUNC_INFO << "nom" << salle.getNom() << "indiceCO2" << salle.getIndiceCO2();

    tableauSallesEco->setRowCount(tableauSallesEco->rowCount() + 1);

    QTableWidgetItem* elementNom = new QTableWidgetItem(salle.getNom());
    elementNom->setFlags(Qt::ItemIsEnabled);
    elementNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1, COLONNE_SALLE_NOM, elementNom);

    QTableWidgetItem* elementDisponibilite = new QTableWidgetItem(QString());
    elementDisponibilite->setFlags(Qt::ItemIsEnabled);
    elementDisponibilite->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_DISPONIBILITE,
                              elementDisponibilite);

    QTableWidgetItem* elementQualiteAir =
      new QTableWidgetItem(SalleEco::getIndiceCO2(salle.getIndiceCO2()));
    elementQualiteAir->setFlags(Qt::ItemIsEnabled);
    elementQualiteAir->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_QUALITE_AIR,
                              elementQualiteAir);

    QTableWidgetItem* elementConfortThermique =
      new QTableWidgetItem(SalleEco::getIndiceTHI(salle.getIndiceTHI()));
    elementConfortThermique->setFlags(Qt::ItemIsEnabled);
    elementConfortThermique->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_CONFORT_THERMIQUE,
                              elementConfortThermique);

    QTableWidgetItem* elementFenetres = new QTableWidgetItem(QString());
    elementFenetres->setFlags(Qt::ItemIsEnabled);
    elementFenetres->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_FENETRES,
                              elementFenetres);

    QTableWidgetItem* elementLumieres = new QTableWidgetItem(QString());
    elementLumieres->setFlags(Qt::ItemIsEnabled);
    elementLumieres->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_LUMIERES,
                              elementLumieres);

    // @todo ajouter les éléments des autres colonnes
}

void IHMEcoClassroom::afficherSallesEco()
{
    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();
    QMapIterator<QString, SalleEco*> sallesEco(salles);
    while(sallesEco.hasNext())
    {
        sallesEco.next();
        ajouterSalleEcoTableau(*sallesEco.value());
    }
}
