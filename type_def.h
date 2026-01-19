#pragma once 
#include <string>
#include <iostream>

using namespace std;



struct personne
{ 
    string name;
    string surname;
    int year;
    int sex;
    personne *conjoint;
    personne *pere;
    personne *mere;
}; 


