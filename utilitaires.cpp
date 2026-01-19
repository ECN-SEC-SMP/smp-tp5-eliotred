#include <string>      
#include <iostream>   
#include "type_def.h" 
#include "utilitaires.h" 
#include <algorithm>  

using namespace std;  

/*
 * Crée une personne dynamiquement et initialise tous ses champs
 */
personne* creerpersonne(string name1, string nom1, int annee1, int genre1)
{
    // Allocation dynamique d'une structure personne
    personne* ptr = new personne;

    // Initialisation des informations personnelles
    ptr->name    = name1;   // Prénom
    ptr->surname = nom1;    // Nom
    ptr->year    = annee1;  // Année de naissance
    ptr->sex     = genre1;  // Sexe (ex: 1 = homme, 0 = femme)

    // Initialisation des pointeurs familiaux à nullptr
    // (la personne n’a encore aucun lien)
    ptr->conjoint = nullptr;
    ptr->pere     = nullptr;
    ptr->mere     = nullptr;

    // Retourne le pointeur vers la personne créée
    return ptr;
}

/*
 * Marier deux personnes si le mariage est autorisé
 */
void marriage(personne* personne1, personne* personne2)
{
    // Vérifie si le mariage est possible selon les règles
    if (mariageposs(personne1, personne2)) {

        // Chaque personne devient le conjoint de l’autre
        personne1->conjoint = personne2;
        personne2->conjoint = personne1;
    }
}

/*
 * Affiche toutes les informations d'une personne
 */
void affichage(personne* personne1)
{
    // Si la personne n’a pas de conjoint
    if (personne1->conjoint == nullptr) {

        // Cas homme
        if (personne1->sex == 1) {
            cout << "Monsieur "
                 << personne1->name << " "
                 << personne1->surname
                 << " pas marie" << endl;
        }
        // Cas femme
        else {
            cout << "Madame "
                 << personne1->name << " "
                 << personne1->surname
                 << " pas mariee" << endl;
        }
    }
    // Si la personne est mariée et est un homme
    else if (personne1->sex == 1) {
        cout << "Monsieur "
             << personne1->name << " "
             << personne1->surname
             << " epoux de Mme. "
             << personne1->conjoint->surname << endl;
    }
    // Si la personne est mariée et est une femme
    else {
        cout << "Madame "
             << personne1->name << " "
             << personne1->surname
             << " epouse de M. "
             << personne1->conjoint->surname << endl;
    }

    // ----- Affichage du père -----

    // Si le père est inconnu
    if (personne1->pere == nullptr) {
        cout << "De pere inconnu" << endl;
    }
    // Si le père est connu
    else {
        cout << "De pere "
             << personne1->pere->name << " "
             << personne1->pere->surname << endl;
    }

    // ----- Affichage de la mère -----

    // Si la mère est inconnue
    if (personne1->mere == nullptr) {
        cout << "De mere inconnue" << endl;
    }
    else {
        // Si la mère n’est pas mariée
        if (personne1->mere->conjoint == nullptr) {
            cout << "De mere "
                 << personne1->mere->name << " "
                 << personne1->mere->surname
                 << " non mariee" << endl;
        }
        // Si la mère est mariée
        else {
            cout << "De mere "
                 << personne1->mere->name << " "
                 << personne1->mere->surname
                 << " epouse de M. "
                 << personne1->mere->conjoint->surname << endl;
        }
    }
}

/*
 * Vérifie si deux personnes sont exactement les mêmes
 */
bool memepersonne(personne* personne1, personne* personne2)
{
    // Sécurité : si un des pointeurs est nul
    if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }

    // Compare tous les champs significatifs
    return (personne1->name    == personne2->name &&
            personne1->surname == personne2->surname &&
            personne1->year    == personne2->year &&
            personne1->sex     == personne2->sex);
}

/*
 * Vérifie si deux personnes sont frère et sœur
 */
bool frereetsoeur(personne* personne1, personne* personne2)
{
    // Sécurité
    if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }

    // Une personne ne peut pas être son propre frère ou sœur
    if (memepersonne(personne1, personne2)) {
        return false;
    }

    // Même père ET même mère, tous deux connus
    if (personne1->pere == personne2->pere &&
        personne1->mere == personne2->mere &&
        personne1->pere != nullptr &&
        personne1->mere != nullptr) {

        return true;
    }

    return false;
}

/*
 * Vérifie si personne2 est un ancêtre de personne1
 */
bool ancetre(personne* personne1, personne* personne2)
{
    // Sécurité
    if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }

    // Une personne n’est pas son propre ancêtre
    // ni l’ancêtre de son frère/sa sœur
    if (memepersonne(personne1, personne2) ||
        frereetsoeur(personne1, personne2)) {
        return false;
    }

    // Cas direct : père ou mère
    if (personne1->pere == personne2 ||
        personne1->mere == personne2) {
        return true;
    }

    // Recherche récursive dans la branche du père
    if (personne1->pere != nullptr &&
        ancetre(personne1->pere, personne2)) {
        return true;
    }

    // Recherche récursive dans la branche de la mère
    if (personne1->mere != nullptr &&
        ancetre(personne1->mere, personne2)) {
        return true;
    }

    // Aucun lien d’ancêtre trouvé
    return false;
}

/*
 * Calcule le nombre maximal de générations d’un arbre
 */
int generation(personne* personne1)
{
    // Cas de base : pas de personne
    if (personne1 == nullptr) {
        return 0;
    }
    else {
        // 1 (la personne actuelle) + la génération maximale
        // entre le père et la mère
        return 1 + max(generation(personne1->pere),
                       generation(personne1->mere));
    }
}

/*
 * Calcule le nombre total de personnes dans l’arbre
 */
int taillearbre(personne* personne1)
{
    // Cas de base
    if (personne1 == nullptr) {
        return 0;
    }
    else {
        // 1 pour la personne actuelle +
        // taille de l’arbre du père +
        // taille de l’arbre de la mère
        return 1 + taillearbre(personne1->pere)
                 + taillearbre(personne1->mere);
    }
}

/*
 * Vérifie si deux personnes peuvent se marier
 */
bool mariageposs(personne* personne1, personne* personne2)
{
    // Interdit si l’un est ancêtre de l’autre
    if (ancetre(personne1, personne2)) {
        return false;
    }

    if (ancetre(personne2, personne1)) {
        return false;
    }

    // Interdit si frère et sœur
    if (frereetsoeur(personne1, personne2)) {
        return false;
    }

    // Interdit si c’est la même personne
    if (memepersonne(personne1, personne2)) {
        return false;
    }

    // Sinon le mariage est possible
    return true;
}

/*
 * Parcours récursif de l’arbre généalogique
 * puis affichage de chaque personne
 */
void affi(personne* t)
{
    // Cas de base
    if (t == nullptr) {
        return;
    }

    // Parcours récursif du père
    if (t->pere != nullptr) {
        affi(t->pere);
    }

    // Parcours récursif de la mère
    if (t->mere != nullptr) {
        affi(t->mere);
    }

    // Affichage de la personne courante
    affichage(t);
}


