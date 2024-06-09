#!/bin/bash
# Projet EcoClassroom 2024
# Simulateur d'une salle en mode pas à pas

# Salle
SALLE="B11"

# Broker MQTT
MOSQUITTO_PUB="mosquitto_pub"
BROKER_MQTT="127.0.0.1"

# Topic MQTT
# {racine}/{salle}/{module}/{donnee}
# {racine} = salles
# {module} = sonde | detection
# {donnee} = temperature | humidite | co2 | lumiere | presence | fenetre
TOPIC_RACINE="salles"
TOPIC_TEMPERATURE="${TOPIC_RACINE}/${SALLE}/sonde/temperature"
TOPIC_HUMIDITE="${TOPIC_RACINE}/${SALLE}/sonde/humidite"
TOPIC_CO2="${TOPIC_RACINE}/${SALLE}/sonde/co2"
TOPIC_LUMIERE="${TOPIC_RACINE}/${SALLE}/detection/lumiere"
TOPIC_PRESENCE="${TOPIC_RACINE}/${SALLE}/detection/presence"
TOPIC_FENETRE="${TOPIC_RACINE}/${SALLE}/detection/fenetre"

# Les données d'une salle
declare -a mesuresTemperature=("24" "24" "24.2" "24.1" "24.2" "24.4" "24.5" "24.4" "24.6" "24.7")
declare -a mesuresHumidite=("54" "54" "55" "54" "55" "56" "57" "58" "59" "60")
declare -a mesuresCO2=("312" "455" "380" "658" "889" "905" "1100" "1540" "1422" "1250")
declare -a etatsFenetre=("0" "0" "0" "0" "0" "1" "1" "0" "0" "1")
declare -a etatsPresence=("0" "1" "0" "0" "0" "1" "1" "1" "1" "0")
declare -a etatsLumiere=("0" "0" "1" "0" "0" "1" "1" "1" "0" "0")

# Programme principal
NB_MESURES=${#mesuresTemperature[*]}
APPUI_TOUCHE="read -s -n 1"

echo -ne "\x1B[93m" # jaune
echo "================================="
echo "Simulateur EcoClassroom 2024     "
echo "Salle ${SALLE}                 "
echo "================================="
echo -ne "\033[0m"
echo

# Simulation
#echo "Nb mesures : ${NB_MESURES}"
echo -ne "\x1B[95m" # violet
echo "*******************************************************************"
echo -ne "\033[0m"
for((n=1;n<$NB_MESURES;n++))
    do
        echo -ne "\x1B[31m" # rouge
        echo "Mesure n°$n"
        echo -ne "\033[0m"
        # module sonde
        echo -ne "\x1B[32m" # vert
        echo "Module sonde"
        echo -ne "\033[0m"
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_TEMPERATURE} -m ${mesuresTemperature[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_TEMPERATURE} -m ${mesuresTemperature[${n}]}
        ${APPUI_TOUCHE} <&1
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_HUMIDITE} -m ${mesuresHumidite[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_HUMIDITE} -m ${mesuresHumidite[${n}]}
        ${APPUI_TOUCHE} <&1
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_CO2} -m ${mesuresCO2[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_CO2} -m ${mesuresCO2[${n}]}
        ${APPUI_TOUCHE} <&1
        # module détection
        echo -ne "\x1B[94m" # bleu
        echo "Module détection"
        echo -ne "\033[0m"
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_LUMIERE} -m ${etatsLumiere[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_LUMIERE} -m ${etatsLumiere[${n}]}
        ${APPUI_TOUCHE} <&1
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_PRESENCE} -m ${etatsPresence[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_PRESENCE} -m ${etatsPresence[${n}]}
        ${APPUI_TOUCHE} <&1
        echo ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_FENETRE} -m ${etatsFenetre[${n}]}
        ${MOSQUITTO_PUB} -h ${BROKER_MQTT} -t ${TOPIC_FENETRE} -m ${etatsFenetre[${n}]}
        ${APPUI_TOUCHE} <&1
        echo -ne "\x1B[95m" # violet
        echo "*******************************************************************"
        echo -ne "\033[0m"
        clear
done

echo -ne "\x1B[93m" # jaune
echo "Fini                             "
echo -ne "\033[0m"
exit 0
