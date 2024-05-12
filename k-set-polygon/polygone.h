#ifndef POLYGONE_H
#define POLYGONE_H

#include "sommet.h"

class Polygone
{
public:
	// constructeur par défaut
	Polygone() : d_premier{ nullptr } {}
	Polygone(Sommet* premier);
	Polygone(Sommet* premier, Sommet* minn, Sommet* maxx);

	// destructeur
	//~Polygone();
	// accesseurs
	Sommet* premier() const { return d_premier; }

	// Ajoute un nouveau sommet au polygone. Les coordonnées du sommet à ajouter sont celles du point p.
	// sommetPrecedent est soit un pointeur sur l’un des sommets déjà présents dans le polygone,
	// soit un pointeur nul si le polygone est vide.
	// Dans le premier cas, le nouveau sommet devient le successeur du sommet d’adresse sommetPrecedent.
	// Dans le deuxième cas, le nouveau sommet devient l’unique sommet du polygone.
	// Dans tous les cas, la méthode renvoie l’adresse du nouveau sommet.
	Sommet* ajouteSommet(const Point& p, Sommet* sommetPrecedent = nullptr);

	// Supprime le sommet d’adresse s du polygone.
	// On suppose que s est effectivement présent dans le polygone.
	void supprimeSommet(Sommet* s);
	Sommet* fusionConvexes(Sommet* x, Sommet* y);
	void setMin(Sommet* s);
	void setMax(Sommet* s);
	Sommet* getMin();
	Sommet* getMax();

	void affiche();


private:
	// un sommet quelconque du polygone. nullptr si le polygone est vide
	Sommet* d_premier;
	Sommet* d_min;
	Sommet* d_max;
};

#endif
