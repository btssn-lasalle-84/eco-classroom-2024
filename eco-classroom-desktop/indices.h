#ifndef INDICES_H
#define INDICES_H

/**
 * @enum IndiceQualiteAir
 * @brief Définit les différentes colonne du tableau
 */
enum IndiceQualiteAir
{
    Inconnu    = 0,
    Excellente = 1,
    TresBien,
    Modere,
    Mauvais,
    TresMauvais,
    Severe,
    NbIndicesQualiteAir
};

/**
 * @enum IndiceTHI
 * @brief Définit les différentes valeurs
 */
enum IndiceTHI
{
    InconnuTHI = -4,
    Froid      = -3,
    Frais,
    LegerementFrais,
    Neutre,
    LegerementTiede,
    Tiede,
    Chaud,
    NbIndicesTHI
};

/**
 * @enum IndiceInconfortIADI
 * @brief Définit les différentes valeurs
 */
enum IndiceInconfortIADI
{
    Aucun = 0,
    Gene  = 1,
    MalEtre,
    Inconfort,
    StressIntense,
    UrgenceMedicale,
    NbIndicesIADI
};

/**
 * @enum IndiceConfinement
 * @brief Définit les différentes valeurs
 */
enum IndiceConfinement
{
    Nul    = 0,
    Faible = 1,
    Moyen,
    Eleve,
    TresEleve,
    Extreme,
    NbIndicesConfinement
};

#endif // INDICES_H
