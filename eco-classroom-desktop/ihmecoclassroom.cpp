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
    dialogueMQTT(new DialogueMQTT(this)), filtrageCourant(Filtrage::Toutes)
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees->connecter();

    recupererSalles();
    creerFenetrePrincipale();
    afficherSallesEco();

    gererEvenements();

    // selectionnerSalleSpecifique(0, COLONNE_SALLE_NOM);
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

void IHMEcoClassroom::afficherEtatFenetre(QString nomSalleEco, QString etat)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "etat" << etat;
    // recherche nomSalleEco dans le tableau des salles affichées
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementNom = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_FENETRES);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, etat);
            return;
        }
    }
}

void IHMEcoClassroom::afficherEtatLumiere(QString nomSalleEco, QString etat)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "etat" << etat;
    // recherche nomSalleEco dans le tableau des salles affichées
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementNom = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_LUMIERES);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, etat);
            return;
        }
    }
}

void IHMEcoClassroom::afficherEtatPresence(QString nomSalleEco, QString etat)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "etat" << etat;
    if(filtrageCourant == Disponibles)
    {
        // Rafraîchit le tableau
        effacerTableauSallesEco();
        afficherSallesEco();
    }
    // recherche nomSalleEco dans le tableau des salles affichées
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementNom = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementNom->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_DISPONIBILITE);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, etat);
            return;
        }
    }
}

void IHMEcoClassroom::afficherIntervention(QString nomSalleEco, QString intervention)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "intervention" << intervention;
    if(filtrageCourant == Interventions)
    {
        effacerTableauSallesEco();
        afficherSallesEco();
    }
    for(int i = 0; i < tableauSallesEco->rowCount(); i++)
    {
        QTableWidgetItem* elementInterventions = tableauSallesEco->item(i, COLONNE_SALLE_NOM);
        if(elementInterventions->data(0).toString() == nomSalleEco)
        {
            QTableWidgetItem* element = tableauSallesEco->item(i, COLONNE_SALLE_INTERVENTIONS);
            if(element != nullptr)
                element->setData(Qt::DisplayRole, intervention);
            return;
        }
    }
}

void IHMEcoClassroom::afficherNouvelleDonnee(QString nomSalleEco,
                                             QString typeDonnee,
                                             QString donnee)
{
    qDebug() << Q_FUNC_INFO << "nomSalleEco" << nomSalleEco << "typeDonnee" << typeDonnee
             << "donnee" << donnee;
    if(nomSalleEco == nomSalle->text())
    {
        afficherSalleSpecifique(salles[nomSalleEco]);
    }
}

void IHMEcoClassroom::selectionnerFiltrage(int indexFiltrage)
{
    qDebug() << Q_FUNC_INFO << "indexFiltrage" << indexFiltrage;
    filtrageCourant = (Filtrage)indexFiltrage;

    effacerTableauSallesEco();
    afficherSallesEco();
}

void IHMEcoClassroom::selectionnerSalleSpecifique(int ligne, int colonne)
{
    QTableWidgetItem* salleEco    = tableauSallesEco->item(ligne, COLONNE_SALLE_NOM);
    QString           nomSalleEco = salleEco->data(0).toString();

    if(salleEco != nullptr)
    {
        afficherSalleSpecifique(salles[salleEco->data(0).toString()]);
    }
}

void IHMEcoClassroom::afficherSalleSpecifique(SalleEco* salleEco)
{
    if(salleEco == nullptr)
        return;
    nomSalle->setText(salleEco->getNom());
    descriptionSalle->setText(salleEco->getDescription());
    superficieSalle->setText(QString::number(salleEco->getSuperficie()) + " m²");
    co2Salle->setText(QString::number(salleEco->getMesureCO2().co2) + " ppm");
    temperatureSalle->setText(QString::number(salleEco->getTemperature().temperature) + " °C");
    humiditeSalle->setText(QString::number(salleEco->getHumidite().humidite) + " %");
    presenceSalle->setText(salleEco->getPresence(salleEco->getEtatPresence()));
    lumieresSalle->setText(salleEco->getLumieres(salleEco->getEtatLumieres()));
    fenetresSalle->setText(salleEco->getFenetres(salleEco->getEtatFenetres()));
    qualiteAirSalle->setText(salleEco->getIndiceCO2(salleEco->getIndiceCO2()));
    confortSalle->setText(salleEco->getIndiceTHI(salleEco->getIndiceTHI()));
    // @todo ajouter alertes
}

void IHMEcoClassroom::creerFenetrePrincipale()
{
    creerStructureFenetrePrincipale();
    creerSelectionFiltrage();
    creerTableauSallesEco();
    creerSalleSpecifique();
    positionnerElementsFenetrePrincipale();
}

void IHMEcoClassroom::creerStructureFenetrePrincipale()
{
    layoutPrincipal       = new QVBoxLayout;
    layoutVueGenerale     = new QVBoxLayout;
    layoutVueFiltrage     = new QHBoxLayout;
    layoutVueTableau      = new QHBoxLayout;
    cadreSalleSpecifique  = new QFrame(this);
    layoutVueSpecifique   = new QVBoxLayout;
    layoutVueInformations = new QHBoxLayout;
    layoutVueDescription  = new QHBoxLayout;
    layoutVueDonnees      = new QHBoxLayout;
    layoutVueGauche       = new QVBoxLayout;
    layoutVueCentrale     = new QVBoxLayout;
    layoutVueDroite       = new QVBoxLayout;

    layoutVueGenerale->addLayout(layoutVueFiltrage);
    layoutVueGenerale->addLayout(layoutVueTableau);
    layoutVueSpecifique->addLayout(layoutVueInformations);
    layoutVueSpecifique->addLayout(layoutVueDescription);
    layoutVueGauche->setAlignment(Qt::AlignCenter);
    layoutVueDonnees->addLayout(layoutVueGauche);
    layoutVueCentrale->setAlignment(Qt::AlignCenter);
    layoutVueDonnees->addLayout(layoutVueCentrale);
    layoutVueDroite->setAlignment(Qt::AlignCenter);
    layoutVueDonnees->addLayout(layoutVueDroite);
    layoutVueSpecifique->addLayout(layoutVueDonnees);
    layoutPrincipal->addLayout(layoutVueGenerale);
    layoutPrincipal->addSpacing(50);
    cadreSalleSpecifique->setFrameStyle(QFrame::Panel | QFrame::Raised);
    cadreSalleSpecifique->setLineWidth(2);
    cadreSalleSpecifique->setLayout(layoutVueSpecifique);
    layoutPrincipal->addWidget(cadreSalleSpecifique);

    setLayout(layoutPrincipal);
}

void IHMEcoClassroom::creerSelectionFiltrage()
{
    choixFiltrage = new QComboBox(this);

    choixFiltrage->addItem("Toutes");
    choixFiltrage->addItem("Disponibles");
    choixFiltrage->addItem("Interventions");
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
}

void IHMEcoClassroom::creerSalleSpecifique()
{
    this->setStyleSheet("QLabel { font-family: 'Open Sans'; font-size: 24px; }");
    nomSalle = new QLabel("---", cadreSalleSpecifique);
    // nomSalle->setObjectName("nomSalle"); // QSS : QLabel#nomSalle { }
    nomSalle->setStyleSheet("font-size: 50px; color: red; font: bold;");
    superficieSalle = new QLabel(cadreSalleSpecifique);
    superficieSalle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    descriptionSalle = new QLabel(cadreSalleSpecifique);
    descriptionSalle->setStyleSheet("font: bold;");
    co2Salle = new QLabel(cadreSalleSpecifique);
    co2Salle->setAlignment(Qt::AlignCenter);
    temperatureSalle = new QLabel(cadreSalleSpecifique);
    temperatureSalle->setAlignment(Qt::AlignCenter);
    humiditeSalle = new QLabel(cadreSalleSpecifique);
    humiditeSalle->setAlignment(Qt::AlignCenter);
    presenceSalle = new QLabel(cadreSalleSpecifique);
    presenceSalle->setAlignment(Qt::AlignCenter);
    lumieresSalle = new QLabel(cadreSalleSpecifique);
    lumieresSalle->setAlignment(Qt::AlignCenter);
    fenetresSalle = new QLabel(cadreSalleSpecifique);
    fenetresSalle->setAlignment(Qt::AlignCenter);
    qualiteAirSalle = new QLabel(cadreSalleSpecifique);
    qualiteAirSalle->setAlignment(Qt::AlignCenter);
    confortSalle = new QLabel(cadreSalleSpecifique);
    confortSalle->setAlignment(Qt::AlignCenter);
    alertesSalle = new QLabel(cadreSalleSpecifique);
    alertesSalle->setAlignment(Qt::AlignCenter);
}

void IHMEcoClassroom::positionnerElementsFenetrePrincipale()
{
    layoutVueFiltrage->addWidget(choixFiltrage);
    layoutVueFiltrage->addStretch();
    layoutVueTableau->addWidget(tableauSallesEco);
    layoutVueInformations->addWidget(nomSalle);
    layoutVueInformations->addStretch();
    layoutVueInformations->addWidget(superficieSalle);
    layoutVueDescription->addWidget(descriptionSalle);
    layoutVueGauche->addWidget(co2Salle);
    layoutVueGauche->addWidget(presenceSalle);
    layoutVueGauche->addWidget(qualiteAirSalle);
    layoutVueCentrale->addWidget(temperatureSalle);
    layoutVueCentrale->addWidget(fenetresSalle);
    layoutVueCentrale->addWidget(confortSalle);
    layoutVueDroite->addWidget(humiditeSalle);
    layoutVueDroite->addWidget(lumieresSalle);
    layoutVueDroite->addWidget(alertesSalle);
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
        connect(sallesEco.value(),
                SIGNAL(nouvelEtatFenetre(QString, QString)),
                this,
                SLOT(afficherEtatFenetre(QString, QString)));
        connect(sallesEco.value(),
                SIGNAL(nouvelEtatLumiere(QString, QString)),
                this,
                SLOT(afficherEtatLumiere(QString, QString)));
        connect(sallesEco.value(),
                SIGNAL(nouvelEtatPresence(QString, QString)),
                this,
                SLOT(afficherEtatPresence(QString, QString)));
        connect(tableauSallesEco,
                SIGNAL(cellClicked(int, int)),
                this,
                SLOT(selectionnerSalleSpecifique(int, int)));
    }
    connect(dialogueMQTT,
            SIGNAL(nouvelleDonnee(QString, QString, QString)),
            this,
            SLOT(afficherNouvelleDonnee(QString, QString, QString)));
    connect(choixFiltrage, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionnerFiltrage(int)));
}

void IHMEcoClassroom::ajouterSalleEcoTableau(const SalleEco& salle)
{
    qDebug() << Q_FUNC_INFO << "elementNom" << salle.getNom() << "elementDisponibilite"
             << SalleEco::getPresence(salle.getEtatPresence()) << "elementQualiteAir"
             << SalleEco::getIndiceCO2(salle.getIndiceCO2()) << "elementConfortThermique"
             << SalleEco::getIndiceTHI(salle.getIndiceTHI()) << "elementFenetres"
             << SalleEco::getFenetres(salle.getEtatFenetres()) << "elementLumieres"
             << SalleEco::getLumieres(salle.getEtatLumieres());

    tableauSallesEco->setRowCount(tableauSallesEco->rowCount() + 1);

    QTableWidgetItem* elementNom = new QTableWidgetItem(salle.getNom());
    elementNom->setFlags(Qt::ItemIsEnabled);
    elementNom->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1, COLONNE_SALLE_NOM, elementNom);

    QTableWidgetItem* elementDisponibilite =
      new QTableWidgetItem(SalleEco::getPresence(salle.getEtatPresence()));
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

    QTableWidgetItem* elementFenetres =
      new QTableWidgetItem(SalleEco::getFenetres(salle.getEtatFenetres()));
    elementFenetres->setFlags(Qt::ItemIsEnabled);
    elementFenetres->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_FENETRES,
                              elementFenetres);

    QTableWidgetItem* elementLumieres =
      new QTableWidgetItem(SalleEco::getLumieres(salle.getEtatLumieres()));
    elementLumieres->setFlags(Qt::ItemIsEnabled);
    elementLumieres->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_LUMIERES,
                              elementLumieres);

    QString messageIntervention;
    if(salle.getFiltreeIntervention())
        messageIntervention = salle.getMessageIntervention();
    QTableWidgetItem* elementInterventions = new QTableWidgetItem();
    elementInterventions->setFlags(Qt::ItemIsEnabled);
    elementInterventions->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    elementInterventions->setText(messageIntervention);
    tableauSallesEco->setItem(tableauSallesEco->rowCount() - 1,
                              COLONNE_SALLE_INTERVENTIONS,
                              elementInterventions);
}

void IHMEcoClassroom::afficherSallesEco()
{
    qDebug() << Q_FUNC_INFO << "Nb salles" << salles.size();
    QMapIterator<QString, SalleEco*> sallesEco(salles);
    while(sallesEco.hasNext())
    {
        sallesEco.next();
        if(sallesEco.value()->estFiltre(filtrageCourant))
        {
            ajouterSalleEcoTableau(*sallesEco.value());
        }
    }
}

void IHMEcoClassroom::effacerTableauSallesEco()
{
    int nb = tableauSallesEco->rowCount();
    if(nb != 0)
    {
        for(int n = 0; n < nb; n++)
            tableauSallesEco->removeRow(0);
    }
}
