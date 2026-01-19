#pragma once 
#include <string>
#include <iostream>
#include "type_def.h"


using namespace std;


personne *creerpersonne (string name1, string nom1, int annee1, int genre1);

void marriage (personne* personne1, personne* personne2);

void affichage (personne* personne1, personne* personne2);

bool memepersonne (personne* personne1, personne* personne2);

bool frereetsoeur (personne* personne1, personne* personne2);

bool ancetre (personne* personne1, personne* personne2);

int generation (personne* personne1);

int taillearbre (personne* personne1);

bool mariageposs (personne* personne1, personne* personne2);

void affi(personne* personne1);

void affichage (personne* personne1);