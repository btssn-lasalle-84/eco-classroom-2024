![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=plastic) ![Android Badge](https://img.shields.io/badge/Android-3DDC84?logo=android&logoColor=fff&style=plastic)

[![qt-build](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/make-qt.yml/badge.svg)](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/make-qt.yml) [![android-build](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/android-build.yml/badge.svg)](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/android-build.yml) [![pages-build-deployment](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/pages/pages-build-deployment/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/eco-classroom-2024/actions/workflows/pages/pages-build-deployment)

# Le projet eco-classroom 2024

- [Le projet eco-classroom 2024](#le-projet-eco-classroom-2024)
  - [Présentation](#présentation)
  - [Fonctionnalités](#fonctionnalités)
  - [Documentation du code](#documentation-du-code)
  - [Tickets Jira](#tickets-jira)
  - [Diagramme de classes](#diagramme-de-classes)
    - [EcoClassroom-desktop (C++/Qt)](#ecoclassroom-desktopcqt)
  - [Diagramme de cas d'utilisation](#diagramme-de-cas-dutilisation)
    - [Quizzy-desktop (C++/Qt)](#quizzy-desktopcqt)
  - [Protocole](#protocole)
  - [Itérations](#itérations)
    - [Itération 1](#itération-1)
    - [Itération 2](#itération-2)
    - [Itération 3](#itération-3)
  - [Screenshots](#screenshots)
  - [Historique des versions](#historique-des-versions)
    - [Version 0.1](#version-01)
      - [Desktop](#desktop)
  - [Recette](#recette)
  - [Auteurs](#auteurs)

---

## Présentation

Le système assure une supervision de salles dans un établissement scolaire. Chaque salle sera équipée de deux modules connectés afin de détecter et mesurer l’état de celle-ci.

Les informations seront accessibles à partir d’une tablette ou d’une application PC permettant aux personnels d’assurer un suivi et d’intervenir en conséquence.

## Fonctionnalités


## Documentation du code

https://btssn-lasalle-84.github.io/eco-classroom-2024/


## Tickets Jira

![Tickets jira](images/tickets_jira.png)
## Diagramme de classes

### EcoClassroom-desktop (C++/Qt)

![Diagramme de classe](images/diagramme_classes.png)
## Diagramme de cas d'utilisation

### Quizzy-desktop (C++/Qt)

![Diagramme cas d'utilisation](images/diagramme_cas_utilisations.png)

## Protocole

## Itérations

### Itération 1

- **Affichage IHM** : L'utilisateur peut avoir un aperçu des salles dans un tableau.
- **Connexion base de données** : L'application est relié à la base de données.
- **Calcul des indices** : Les indices sont calculés et affichés dans l'IHM.

### Itération 2

- **Filtrer les salles** : L'utilisateur peut effectuer une recherche avec des critères précis.
- **Affichage d'une salle spécifique** : L'utilisateur peut visualiser une salle spécifique.
- **Communiquer avec les modules** : L'application communique avec les différents modules.

### Itération 3

- **Editer une salle** : L'utilisateur peut éditer des informations sur une salle spécifique.
- **Signalement dépassement de seuils** : L'application affiche les dépassements de seuils des salles.



## Screenshots

## Historique des versions

### Version 0.1

#### Desktop

- Afficher un tableau de l'ensemble des salles
- Relié à la base de données

## Recette

| Fonctionnalités   | Oui | Non |
|--------------------|-----|-----|
| Affichage IHM principale  |  X  |     |
| Récuperer l'ensemble des salles |  X  |   |
| Calcul des indices         |    |   X  |



## Auteurs

- Étudiant IR : VIGNAL Thomas <<thomasvignal.btssn@gmail.com>>
- Étudiant IR : VALOBRA Enzo <<valobra.enzo@gmail.com>>

---
©️ LaSalle Avignon 2024