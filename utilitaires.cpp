
#include <string>
#include <iostream>
#include "type_def.h"
#include "utilitaires.h"
#include <algorithm>

using namespace std;

personne *creerpersonne ( string name1, string nom1, int annee1, int genre1)
{
   personne* ptr = new personne; 

   ptr->name = name1;

   ptr->surname = nom1;

   ptr->year = annee1;

   ptr->sex = genre1;
 
   ptr->conjoint = nullptr;

   ptr->pere = nullptr;

   ptr->mere = nullptr;




  return ptr;
}

void marriage (personne* personne1, personne* personne2)
{

    if (mariageposs(personne1, personne2)) {
        personne1->conjoint=personne2;

        personne2->conjoint=personne1;
    }


}

void affichage (personne* personne1)
{
  if(personne1->conjoint==nullptr){
    if (personne1->sex==1){
        
            cout<<"Monsieur"<<" "<<personne1->name<<" "<<personne1->surname<<" "<<"pas marrie"<<endl;

    } else {

             cout<<"Madame"<<" "<<personne1->name<<" "<<personne1->surname<<" "<<"pas marrie"<<endl;
    }

  } else if (personne1->sex==1){

            cout<<"Monsieur"<<" "<<personne1->name<<" "<<personne1->surname<<" "<<"epoux de Mme. "<<(personne1->conjoint)->surname<<endl;

  } else if (personne1->sex==0){

              cout<<"Madame"<<" "<<personne1->name<<" "<<personne1->surname<<" "<<"epouse de M."<<(personne1->conjoint)->surname<<endl;

  }


  if (personne1->pere==nullptr){
        cout<<"De pere inconnu"<<endl;

  } else {

        cout<<"De pere"<<" "<<(personne1->pere)->name<<" "<<(personne1->pere)->surname<<endl;

  } if (personne1->mere==nullptr){

        cout<<"De mere inconnu"<<endl;

  } else {
     
    if((personne1->mere)->conjoint==nullptr){
        cout<<"De mere"<<" "<<(personne1->mere)->name<<" "<<(personne1->mere)->surname<<" "<<"non marrie"<<endl;

    } else {
     
        cout<<"De mere"<<" "<<(personne1->mere)->name<<" "<<(personne1->mere)->surname<<" "<<"epouse de M."<<((personne1->mere)->conjoint)->surname<<endl;

    }
        
  }
  

}

bool memepersonne (personne* personne1, personne* personne2) {

    if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }




    if (personne1->name==personne2->name && personne1->surname==personne2->surname && personne1->year==personne2->year && personne1->sex ==personne2->sex){

     
       return true; 

    }



       return false;

}

bool frereetsoeur (personne* personne1, personne* personne2){
 

 if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }

 if (memepersonne(personne1, personne2)==1){

  
   return false;

 }


    if (personne1->pere==personne2->pere  && personne1->mere==personne2->mere&&personne1->pere!=nullptr && personne1->mere!=nullptr){ //cette ligne change tout ca si je mettait pas le second "and" tant qu ils ont pas de parents aucun marriage


   

        return true;



    }
  


   return false;


}


bool ancetre (personne* personne1, personne* personne2) {

    

    // Sécurité
    if (personne1 == nullptr || personne2 == nullptr) {
        return false;
    }

    // Une personne n'est pas son propre ancêtre
    if (memepersonne(personne1, personne2) ||
        frereetsoeur(personne1, personne2)) {
        return false;
    }

    // Cas direct : père ou mère
    if (personne1->pere == personne2 ||
        personne1->mere == personne2) {
        return true;
    }

    // Recherche récursive côté père
    if (personne1->pere != nullptr &&
        ancetre(personne1->pere, personne2)) {
        return true;
    }

    // Recherche récursive côté mère
    if (personne1->mere != nullptr &&
        ancetre(personne1->mere, personne2)) {
            
        return true;
    }

  
    return false;




}


int generation (personne* personne1) {

 

  if(personne1==nullptr){

      return 0;

  } else{

     return 1 + max(generation(personne1->pere), generation(personne1->mere));
    }


}

/*int generation(Personne* personne1) {
    if (personne1 == nullptr) {
        return 0;
    } else {
        int genPere = generation(personne1->pere);
        int genMere = generation(personne1->mere);

        // remplacer max par un if
        if (genPere > genMere) {
            return 1 + genPere;
        } else {
            return 1 + genMere;
        }
    }
}*/




int taillearbre (personne* personne1){

    

    if(personne1==nullptr)  {

      return 0;

    }

     else {
        return 1+ taillearbre(personne1->pere) + taillearbre(personne1->mere);
    }

   

}


bool mariageposs (personne* personne1, personne* personne2){

  if (ancetre(personne1, personne2)==1){

    return false;

  }

  if (ancetre(personne2, personne1)==1){

    return false;

  }

  if (frereetsoeur(personne2, personne1)){

    return false;


  }

  if (memepersonne(personne2, personne1)){


     
     return false;
  }



  return true;



}


void affi (personne* t){
 
  if (t == nullptr) {
        return;
    }

 if (t->pere!=nullptr){
 affi(t->pere);}
 if (t->mere!=nullptr){
 affi(t->mere);}

  affichage (t);

}

/*int* maFonction() {
    int* ptr = new int;
    *ptr = 42;
    return ptr;
}

int main() {
    int* ptr = maFonction(); // ptr pointe sur la mémoire allouée
    cout << *ptr << endl;    // OK, affiche 42

    delete ptr;              // libère la mémoire
    ptr = nullptr;           // bonne pratique pour éviter dangling pointer
}
*/


/*Ton code :
int* ptr2;
int* ptr = maFonction(); // ptr pointe sur la mémoire allouée dans la fonction
ptr = ptr2;               // ptr maintenant pointe sur ptr2 (indéterminé !)
delete ptr;               // on tente de libérer ptr

1️⃣ Ce qui se passe vraiment

ptr = maFonction();

maFonction() fait new int, renvoie un pointeur vers ce bloc mémoire.

ptr pointe maintenant sur ce bloc alloué dynamiquement.

ptr = ptr2;

ptr2 n’a pas été initialisé, donc il contient une valeur indéterminée (garbage pointer).

En faisant ptr = ptr2;, tu perds le pointeur vers la mémoire allouée dans maFonction().

Cette mémoire devient inaccessible → fuite mémoire.

delete ptr;

ptr pointe maintenant sur une adresse indéterminée.

delete sur un pointeur non initialisé → comportement indéfini, souvent core dump ou crash.

2️⃣ Résultat

Fuite mémoire : Oui, car la mémoire allouée par maFonction() n’est plus accessible.

Danger de crash : Oui, car tu fais delete sur un pointeur non initialisé (ptr2).

3️⃣ Version correcte

Si tu veux juste copier le pointeur et libérer la mémoire correctement :

int* ptr = maFonction(); // alloue mémoire
int* ptr2 = ptr;         // ptr2 pointe sur la même mémoire
delete ptr;              // libère la mémoire
ptr = nullptr;           // sécurité
ptr2 = nullptr;          // sécurité


✅ Pas de fuite, pas de crash.

4️⃣ Règle clé

Ne jamais écraser un pointeur vers new avant de le delete.

Toujours initialiser les pointeurs avant de les utiliser.

Une seule fois delete par bloc alloué.

Si tu veux, je peux te faire un petit schéma mémoire avec ce cas précis, pour que tu voies clairement où se produit la fuite et le danger.

Veux‑tu que je fasse ça ?

j ai le droit de definit des ptr comme ca int* ptr;

Oui ✅, tu as parfaitement le droit en C++ de déclarer un pointeur comme ça :

int* ptr;

1️⃣ Ce que ça fait

ptr est un pointeur vers un int.

Mais il n’est pas initialisé.

Sa valeur est donc indéterminée (garbage pointer).

Si tu essayes de l’utiliser avant de l’initialiser, tu auras comportement indéfini (crash, core dump…).

2️⃣ Exemple dangereux
int* ptr;       // déclaration seulement
*ptr = 42;      // ❌ on écrit à une adresse indéterminée → crash
delete ptr;     // ❌ on delete un pointeur non initialisé → crash

3️⃣ Exemple sûr

Toujours initialiser un pointeur :

int* ptr = nullptr;   // initialisé à "rien"


Maintenant tu peux tester avant d’utiliser :

if (ptr != nullptr) {
    *ptr = 42;
}


Ou après un new :

ptr = new int;       // alloue la mémoire
*ptr = 42;
delete ptr;          // libère la mémoire
ptr = nullptr;       // sécurité

4️⃣ Règle pratique
Déclaration	Sécurité
int* ptr;	❌ non initialisé, dangereux si utilisé avant new
int* ptr = nullptr;	✅ sûr, peut tester avant d’utiliser
int* ptr = new int;	✅ sûr, mémoire allouée, à delete plus tard

💡 Conclusion
Oui, tu as le droit de faire int* ptr;, mais tu ne dois jamais l’utiliser tant qu’il n’a pas été initialisé avec nullptr ou new.

Si tu veux, je peux te montrer un mini diagramme mémoire avec int* ptr; vs int* ptr = nullptr; pour que ce soit super clair. Veux‑tu que je fasse ça ?*/