#ifndef DIALOGUEMQTT_H
#define DIALOGUEMQTT_H

#include <QObject>
#include <QtMqtt/QtMqtt>

/**
 * @def ADRESSE_IP_BROKER_MQTT
 * @brief L'adresse IP du broker MQTT (Raspeberry Pi Zero)
 */
//#define ADRESSE_IP_BROKER_MQTT "192.168.52.7"

#ifndef ADRESSE_IP_BROKER_MQTT
// Pour les tests, on peut utiliser un broker en local
#define ADRESSE_IP_BROKER_MQTT "127.0.0.1"
#endif // ADRESSE_IP_BROKER_MQTT

/**
 * @def NUMERO_PORT_BROKER_MQTT
 * @brief Le numéro de port par défaut du broker MQTT (Raspeberry Pi Zero)
 */
#define NUMERO_PORT_BROKER_MQTT 1883

/**
 * @def RACINE_DES_TOPICS
 * @brief La racine des topics pour les abonnements (subscribe)
 */
#define RACINE_DES_TOPICS "salles/#"

class DialogueMQTT : public QObject
{
    Q_OBJECT
  public:
    // La structure des topics : salles/nom/type
    enum StructureTopic
    {
        RACINE,            //!< La racine du topic (égal à RACINE_DES_TOPICS)
        NOM_SALLE_ECO,     //!< Le nom de la salle dont provient la donnée
        TYPE_DONNEE_MODULE //!< Le type de données (température, co2, etc...)
    };

  private:
    QMqttClient* clientMQTT; //!< Le client MQTT

  public:
    explicit DialogueMQTT(QObject* parent = nullptr);
    ~DialogueMQTT();

    void demarrer(QString hostname = ADRESSE_IP_BROKER_MQTT,
                  quint16 port     = NUMERO_PORT_BROKER_MQTT);
    void arreter();

  public slots:
    void abonner(QString topic);
    void desabonner(QString topic);
    void recevoirMessage(const QByteArray& message, const QMqttTopicName& topic);
    void gererConnexion();
    void gererDeconnexion();
    void gererErreur();

  signals:
    void brokerConnecte();
    void brokerDeconnecte();
    void nouvelleDonnee(QString nomSalleEco, QString typeDonnee, QString donnee);
};

#endif // DIALOGUEMQTT_H
