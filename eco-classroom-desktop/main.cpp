#include "ihmecoclassroom.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application EcoClassroom
 * @author Thomas VIGNAL
 * @version 0.1
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication    a(argc, argv);
    IHMEcoClassroom ihm;

    QFile fichier(":eco-classroom-desktop.qss");
    if(fichier.open(QFile::ReadOnly))
    {
        QString feuilleStyle = QLatin1String(fichier.readAll());
        a.setStyleSheet(feuilleStyle);
    }
    ihm.show();

    return a.exec();
}
