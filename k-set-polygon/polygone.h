#ifndef POLYGONE_H
#define POLYGONE_H
#include <vector>
#include "sommet.h"
#include "point.h"

class Polygone
{
public:

	// Constructeur par défaut
	Polygone() : d_min(nullptr), d_max(nullptr) {}

	// Constructeur avec des sommets min et max
	Polygone(Sommet* min, Sommet* max) : d_min(min), d_max(max) {}

	//constructeur par recopie
	Polygone(const Polygone& p) : d_min{ p.getMin() }, d_max{ p.getMax() }, t_min{p.getPointsMin()}, t_max{ p.getPointsMax()} {}

	// Getter pour le sommet minimal
	Sommet* getMin() const { return d_min; }

	// Getter pour le sommet maximal
	Sommet* getMax() const { return d_max; }

	// Setter pour le sommet minimal
	void setMin(Sommet* min) { d_min = min; }

	// Setter pour le sommet maximal
	void setMax(Sommet* max) { d_max = max; }

	// Getter pour le tableau de points minimal
	const std::vector<Point*>& getPointsMin() const { return t_min; }

	// Getter pour le tableau de points maximal
	const std::vector<Point*>& getPointsMax() const { return t_max; }
	// constructeur par défaut
	

	// destructeur
	//~Polygone();
	// accesseurs
	

	// Ajoute un nouveau sommet au polygone. Les coordonnées du sommet à ajouter sont celles du point p.
	// sommetPrecedent est soit un pointeur sur l’un des sommets déjà présents dans le polygone,
	// soit un pointeur nul si le polygone est vide.
	// Dans le premier cas, le nouveau sommet devient le successeur du sommet d’adresse sommetPrecedent.
	// Dans le deuxième cas, le nouveau sommet devient l’unique sommet du polygone.
	// Dans tous les cas, la méthode renvoie l’adresse du nouveau sommet.
	Sommet* ajouteSommet(const CentreDeGravite& p, Sommet* sommetPrecedent = nullptr);

	// Supprime le sommet d’adresse s du polygone.
	// On suppose que s est effectivement présent dans le polygone.
	void supprimeSommet(Sommet* s);
	Sommet* fusionConvexes(Sommet* x, Sommet* y);
	Sommet* getMin();
	Sommet* getMax();

	void affiche();


private:
	// un sommet quelconque du polygone. nullptr si le polygone est vide
	
	Sommet* d_min;
	Sommet* d_max;
	std::vector<Point*> t_min;
	std::vector<Point*> t_max;
};

#endif
