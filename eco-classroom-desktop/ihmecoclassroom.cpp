#include "ihmecoclassroom.h"
#include "salleeco.h"
#include "basededonnees.h"
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
    QWidget(parent), baseDeDonnees(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();

    recupererSalles();
    creerTableauSallesEco();
    afficherSallesEco();

    showMaximized();
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
    qDebug() << Q_FUNC_INFO << "nom" << salle.getNom();

    tableauSallesEco->setRowCount(tableauSallesEco->rowCount() + 1);

    QTableWidgetItem* elementNom = new QTableWidgetItem(salle.getNom());
    elementNom->setFlags(Qt::ItemIsEnabled);
    elementNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1, COLONNE_SALLE_NOM, elementNom);

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
