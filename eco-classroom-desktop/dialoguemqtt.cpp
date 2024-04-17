#include "dialoguemqtt.h"
#include <QDebug>

DialogueMQTT::DialogueMQTT(QObject* parent) : QObject(parent), clientMQTT(new QMqttClient(this))
{
    qDebug() << Q_FUNC_INFO;
    demarrer();
}

DialogueMQTT::~DialogueMQTT()
{
    qDebug() << Q_FUNC_INFO;
    arreter();
}

void DialogueMQTT::demarrer(QString hostname, quint16 port)
{
    qDebug() << Q_FUNC_INFO << "hostname" << hostname << "port" << port;

    clientMQTT->setHostname(hostname);
    clientMQTT->setPort(port);

    connect(clientMQTT, SIGNAL(connected(), this, SLOT(gererConnexion());
    connect(clientMQTT, SIGNAL(disconnected()), this, SLOT(gererDeconnexion());
    connect(clientMQTT, SIGNAL(messageReceived()), this, SLOT(recevoirMessage());
    connect(clientMQTT, SIGNAL(errorChanged(ClientError()), this, SLOT(gererErreur());

    clientMQTT->connectToHost();
}

void DialogueMQTT::arreter()
{
    qDebug() << Q_FUNC_INFO;
    clientMQTT->disconnectFromHost();
}

void DialogueMQTT::abonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;

    QMqttSubscription* subscription;

    subscription = clientMQTT->subscribe(topic);
    if(!subscription)
    {
        QMessageBox::critical(this, "Erreur", "Impossible de s'abonner !");
        return;
    }
}

void DialogueMQTT::desabonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;

    QMqttSubscription* unsubscribe;

    clientMQTT->unsubscribe(topic);
}

void DialogueMQTT::recevoirMessage(const QByteArray& message, const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString() << "topic" << topic.name()
             << "message" << message;
    // Les données des modules sonde et détection sont publiées sur le topic : salles/nom/type
    // cf. l'enum StructureTopic

    QStringList topic = topic.name().split('/');


    // @todo Extraire le nom de la salle et le type de donnée

    // @todo Emettre le signal nouvelleDonnee()

    // @todo Il faudra connecter ce signal dans l'IHM pour traiter les données reçues
}

void DialogueMQTT::gererConnexion()
{
    qDebug() << Q_FUNC_INFO;
    // @todo Emettre le signal brokerConnecte() qu'il faudra connecter dans l'IHM pour signaler
    // visuellement que l'on est connecté au broker

    abonner(RACINE_DES_TOPICS);
}

void DialogueMQTT::gererDeconnexion()
{
    qDebug() << Q_FUNC_INFO;
    // @todo Emettre le signal brokerDeconnecte() qu'il faudra connecter dans l'IHM pour signaler
    // visuellement que l'on est déconnecté au broker

    desabonner(RACINE_DES_TOPICS);
}

void DialogueMQTT::gererErreur(QMqttClient::ClientError erreur)
{
    // pour le débuggage
    qDebug() << Q_FUNC_INFO << "erreur" << erreur;
}
