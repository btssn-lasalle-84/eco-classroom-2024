#include "dialoguemqtt.h"
#include <QDebug>

DialogueMQTT::DialogueMQTT(QObject* parent) : QObject(parent), clientMQTT(new QMqttClient(this))
{
    qDebug() << Q_FUNC_INFO;
    // @todo appeler la méthode demarrer()
}

DialogueMQTT::~DialogueMQTT()
{
    // @todo la méthode arreter()
    qDebug() << Q_FUNC_INFO;
}

void DialogueMQTT::demarrer(QString hostname, quint16 port)
{
    qDebug() << Q_FUNC_INFO << "hostname" << hostname << "port" << port;

    // @todo Fixer le Hostname de l'objet clientMQTT

    // @todo Fixer le Port de l'objet clientMQTT

    // @todo Connecter les signaux connected(), disconnected(), messageReceived() et
    // errorChanged(ClientError) aux slots gererConnexion(), gererDeconnexion(), recevoirMessage()
    // et gererErreur()

    // @todo Appeler la méthode connectToHost() de l'objet clientMQTT pour se connecter au broker
}

void DialogueMQTT::arreter()
{
    qDebug() << Q_FUNC_INFO;
    // @todo Appeler la méthode disconnectFromHost() de l'objet clientMQTT pour se connecter au
    // broker
}

void DialogueMQTT::abonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;
    // @todo Appeler la méthode subscribe() de l'objet clientMQTT pour s'abonner au topic
}

void DialogueMQTT::desabonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;
    // @todo Appeler la méthode unsubscribe() de l'objet clientMQTT pour s'abonner au topic
}

void DialogueMQTT::recevoirMessage(const QByteArray& message, const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString() << "topic" << topic.name()
             << "message" << message;
    // Les données des modules sonde et détection sont publiées sur le topic : salles/nom/type
    // cf. l'enum StructureTopic

    // @todo Spliter le topic.name() avec le délimiteur '/'

    // @todo Extraire le nom de la salle et le type de donnée

    // @todo Emettre le signal nouvelleDonnee()

    // @todo Il faudra connecter ce signal dans l'IHM pour traiter les données reçues
}

void DialogueMQTT::gererConnexion()
{
    qDebug() << Q_FUNC_INFO;
    // @todo Emettre le signal brokerConnecte() qu'il faudra connecter dans l'IHM pour signaler
    // visuellement que l'on est connecté au broker

    // @todo Appeler la méthode abonner() pour s'abonner au topic racine des salles
}

void DialogueMQTT::gererDeconnexion()
{
    qDebug() << Q_FUNC_INFO;
    // @todo Emettre le signal brokerDeconnecte() qu'il faudra connecter dans l'IHM pour signaler
    // visuellement que l'on est déconnecté au broker

    // @todo Appeler la méthode desabonner() pour se désabonner du topic racine des salles
}

void DialogueMQTT::gererErreur(QMqttClient::ClientError erreur)
{
    // pour le débuggage
    qDebug() << Q_FUNC_INFO << "erreur" << erreur;
}
