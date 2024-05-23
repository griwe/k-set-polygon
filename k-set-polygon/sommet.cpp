#include "sommet.h"
#include <stdexcept>

using namespace std;

Sommet* Sommet::precedent() const
{
    return this->d_precedent;
}

void Sommet::setSuivant(Sommet* suivant)
{
    this->d_suivant = suivant;
}

void Sommet::setPrecedent(Sommet* precedent)
{
    this->d_precedent = precedent;
}

void Sommet::setAjouter(int ajouter)
{
    this->d_ajouter = ajouter;
}

void Sommet::setEnlever(int enlever)
{
    this->d_enlever = enlever;
}
