#include "sommet.h"

using namespace std;

void Sommet::setSuivant(Sommet* suivant)
{
    this->d_suivant = suivant;
}

void Sommet::setPrecedent(Sommet* precedent)
{
    this->d_precedent = precedent;
}