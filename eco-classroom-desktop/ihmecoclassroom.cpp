#include "ihmecoclassroom.h"
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
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe IHMEcoClassroom
 */
IHMEcoClassroom::~IHMEcoClassroom()
{
    qDebug() << Q_FUNC_INFO;
}
