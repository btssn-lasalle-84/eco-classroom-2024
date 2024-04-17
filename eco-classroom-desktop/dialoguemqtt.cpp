#include "dialoguemqtt.h"
//#include <QMessageBox>
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

    connect(clientMQTT, SIGNAL(connected()), this, SLOT(gererConnexion()));
    connect(clientMQTT, SIGNAL(disconnected()), this, SLOT(gererDeconnexion()));
    connect(clientMQTT,
            SIGNAL(messageReceived(const QByteArray&, const QMqttTopicName&)),
            this,
            SLOT(recevoirMessage(const QByteArray&, const QMqttTopicName&)));
    connect(clientMQTT, SIGNAL(errorChanged(ClientError)), this, SLOT(gererErreur(ClientError)));

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
        // @todo il faut emettre un signal à connecter à un slot de l'ihm pour pouvoir afficher
        // cette boîte de dialogue QMessageBox::critical(this, "Erreur", "Impossible de s'abonner
        // !");
        return;
    }
}

void DialogueMQTT::desabonner(QString topic)
{
    qDebug() << Q_FUNC_INFO << "topic" << topic;

    clientMQTT->unsubscribe(topic);
}

void DialogueMQTT::recevoirMessage(const QByteArray& message, const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString() << "topic" << topic.name()
             << "message" << message;
    // Les données des modules sonde et détection sont publiées sur le topic : salles/nom/type
    // cf. l'enum StructureTopic

    QStringList champs = topic.name().split('/');
    qDebug() << Q_FUNC_INFO << "champs" << champs;

    // @todo Extraire le nom de la salle et le type de donnée

    // @todo Emettre le signal nouvelleDonnee()

    // @todo Il faudra connecter ce signal dans l'IHM pour traiter les données reçues
}

void DialogueMQTT::gererConnexion()
{
    qDebug() << Q_FUNC_INFO;
    emit brokerConnecte();
    abonner(RACINE_DES_TOPICS);
}

void DialogueMQTT::gererDeconnexion()
{
    qDebug() << Q_FUNC_INFO;
    emit brokerDeconnecte();
    desabonner(RACINE_DES_TOPICS);
}

void DialogueMQTT::gererErreur(QMqttClient::ClientError erreur)
{
    // pour le débuggage
    qDebug() << Q_FUNC_INFO << "erreur" << erreur;
}
