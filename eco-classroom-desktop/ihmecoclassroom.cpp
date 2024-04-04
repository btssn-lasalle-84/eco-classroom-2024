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
    creerTableauIHM();
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
    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();

    // Exemple pour parcourir une QMap
    QMapIterator<QString, SalleEco*> sallesEco(salles);
    while(sallesEco.hasNext())
    {
        sallesEco.next();
        qDebug() << Q_FUNC_INFO << "SalleEco" << sallesEco.key();
    }
}

void IHMEcoClassroom::creerTableauIHM()
{
    tableauIHM = new QTableWidget(this);
    tableauIHM->setRowCount(10);
    tableauIHM->setColumnCount(6);

    QStringList labels;
    labels << "Salle"
           << "Disponibilité"
           << "Qualité d'air"
           << "Confort Thermique"
           << "Fenêtres"
           << "Lumières";

    tableauIHM->setHorizontalHeaderLabels(labels);

    tableauIHM->setColumnWidth(0, 100);
    tableauIHM->setColumnWidth(1, 100);
    tableauIHM->setColumnWidth(2, 200);
    tableauIHM->setColumnWidth(3, 200);
    tableauIHM->setColumnWidth(4, 150);
    tableauIHM->setColumnWidth(5, 150);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableauIHM);
    setLayout(layout);
}
