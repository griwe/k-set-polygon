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

bool Sommet::contains(const vector<int> vec, const int indice)
{
	return std::find(vec.begin(), vec.end(), indice) != vec.end();
}

int Sommet::retourneIndice(vector<int> a, vector<int> b)
{
	for (int i = 0; i < a.size(); i++) {
		if (!contains(b, a[i])) {
			return a[i];
		}
	}
	return -1;
}

void Sommet::inialiserAjEnl()
{
	int iAjouter, iEnlever;
	iAjouter = retourneIndice(cdg().ensemble(), precedent()->cdg().ensemble());
	iEnlever = retourneIndice(cdg().ensemble(), suivant()->cdg().ensemble());

	d_ajouter = iAjouter;
	d_enlever = iEnlever;
}
