#ifndef SOMMET_H
#define SOMMET_H

#include "point.h"

class Sommet
{
	friend class Polygone;
public:
	Sommet(const Point& p, Sommet* suivant = nullptr, Sommet* precedent = nullptr)
		: d_coordonnees{ p }, d_suivant{ suivant }, d_precedent{ precedent } {}
	// accesseurs
	Point coordonnees() const { return d_coordonnees; }
	Sommet* suivant() const { return d_suivant; }
	Sommet* precedent() const;
	void setSuivant(Sommet* suivant);
	void setPrecedent(Sommet* precedent);





private:
	// constructeur à partir d'un point p
	
	// destructeur vide privé
	~Sommet() = default;

	// coordonnées
	Point d_coordonnees;
	// sommets suivant et precedent
	Sommet* d_suivant, * d_precedent;
};

#endif
