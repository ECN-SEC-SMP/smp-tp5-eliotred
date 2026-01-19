#include <iostream>
#include <string>
#include "utilitaires.h"
#include "type_def.h"

using namespace std;

int main() {
    // =========================================================
    // 1. CRÉATION DES PERSONNES
    // =========================================================
    // Génération 1
    personne* paul  = creerpersonne("Paul", "Durand", 1950, 1);
    personne* marie = creerpersonne("Marie", "Martin", 1952, 0);

    // Génération 2
    personne* jean   = creerpersonne("Jean", "Durand", 1975, 1);
    personne* claire = creerpersonne("Claire", "Durand", 1978, 0);
    personne* sophie = creerpersonne("Sophie", "Leroy", 1976, 0);

    // Génération 3
    personne* emma = creerpersonne("Emma", "Durand", 2000, 0);

    // =========================================================
    // 2. ÉTABLISSEMENT DES LIENS (Mariages et Parenté)
    // =========================================================
    // Mariages
    marriage(paul, marie);
    marriage(jean, sophie);

    // Filiation Jean et Claire (enfants de Paul et Marie)
    jean->pere = paul;   jean->mere = marie;
    claire->pere = paul; claire->mere = marie;

    // Filiation Emma (enfant de Jean et Sophie)
    emma->pere = jean;
    emma->mere = sophie;

    // =========================================================
    // 3. TESTS D'AFFICHAGE INDIVIDUEL
    // =========================================================
    cout << "--- TEST AFFICHAGE INDIVIDUEL ---" << endl;
    cout << "Focus sur Jean :" << endl;
    affichage(jean);
    cout << "\nFocus sur Emma :" << endl;
    affichage(emma);
    cout << "---------------------------------\n" << endl;

    // =========================================================
    // 4. TESTS DES FONCTIONS LOGIQUES (Booléens)
    // =========================================================
    cout << "--- TESTS LOGIQUES (1 = Vrai, 0 = Faux) ---" << endl;
    
    cout << "Claire et Jean sont frere/soeur ?     : " << frereetsoeur(claire, jean) << " (Attendu: 1)" << endl;
    cout << "Emma et Claire sont frere/soeur ?     : " << frereetsoeur(emma, claire) << " (Attendu: 0)" << endl;
    
    cout << "Paul est l'ancetre d'Emma ?           : " << ancetre(emma, paul) << " (Attendu: 1)" << endl;
    cout << "Emma est l'ancetre de Paul ?          : " << ancetre(paul, emma) << " (Attendu: 0)" << endl;
    
    cout << "Mariage Emma / Jean (Pere) possible ? : " << mariageposs(emma, jean) << " (Attendu: 0)" << endl;
    cout << "Mariage Emma / Paul (GP) possible ?   : " << mariageposs(emma, paul) << " (Attendu: 0)" << endl;
    cout << "------------------------------------------\n" << endl;

    // =========================================================
    // 5. TESTS DES MESURES DE L'ARBRE
    // =========================================================
    cout << "--- MESURES DE L'ARBRE ---" << endl;
    cout << "Generation de Emma  : " << generation(emma) << " (Attendu: 3)" << endl;
    cout << "Generation de Paul  : " << generation(paul) << " (Attendu: 1)" << endl;
    cout << "Taille arbre (Emma) : " << taillearbre(emma) << " (Attendu: 5 )" << endl;
    cout << "--------------------------\n" << endl;

    // =========================================================
    // 6. PARCOURS COMPLET DE L'ARBRE
    // =========================================================
    cout << "===== PARCOURS COMPLET DE L'ARBRE (Depuis Emma) =====" << endl;
    affi(emma);
    cout << "=====================================================" << endl;

    return 0;
}