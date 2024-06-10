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



void Sommet::inialiserAjEnl()
{
	int iAjouter, iEnlever;
	iAjouter = retourneIndice(cdg().ensemble(), precedent()->cdg().ensemble());
	iEnlever = retourneIndice(cdg().ensemble(), suivant()->cdg().ensemble());

	 d_ajouter = iAjouter;
	 d_enlever = iEnlever;
}
