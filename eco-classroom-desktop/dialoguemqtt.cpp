#include "dialoguemqtt.h"
#include <QMessageBox>
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
    connect(clientMQTT, SIGNAL(errorChanged(ClientError)), this, SLOT(gererErreur()));

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
        QMessageBox::critical(nullptr, "Erreur", "Impossible de s'abonner au broker MQTT !");
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

    emit nouvelleDonnee(champs.at(StructureTopic::NOM_SALLE_ECO),
                        champs.at(StructureTopic::TYPE_DONNEE_MODULE),
                        message);
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

void DialogueMQTT::gererErreur()
{
    // pour le débuggage
    qDebug() << Q_FUNC_INFO << "erreur" << clientMQTT->error();
}
