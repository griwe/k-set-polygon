#include <vector>
using namespace std;

#include "carte.h"
#include "point.h"


// Destructeur
Carte::~Carte()
{
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
// dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
// On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, DemiCote* precedent2)
{
	DemiCote *dc1 = ajouteDemiCote(precedent1);
	DemiCote *dc2 = ajouteDemiCote(precedent2,dc1);

	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
// On suppose precedent1 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, const Point& p2)
{
	DemiCote *dc1 = ajouteDemiCote(precedent1);
	DemiCote *dc2 = ajouteDemiCote(p2,dc1);

	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
// On suppose precedent2 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, DemiCote* precedent2)
{
	DemiCote *dc1 = ajouteDemiCote(p1);
	DemiCote *dc2 = ajouteDemiCote(precedent2,dc1);

	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
// coordonn�es sont celles des points p1 et p2 respectivement.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, const Point& p2)
{
	DemiCote *dc1 = ajouteDemiCote(p1);
	DemiCote *dc2 = ajouteDemiCote(p2,dc1);

	return dc1;
}

// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
// par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(DemiCote* precedent, DemiCote* oppose)
{
	DemiCote *newDC = new DemiCote{precedent->d_suivant, precedent, oppose, precedent->d_sommet, static_cast<int>(d_tabDemiCotes.size())};

	d_tabDemiCotes.push_back(newDC);
	precedent->d_suivant = newDC;
	newDC->d_suivant->d_precedent = newDC;

	if( oppose != nullptr)
    {
        oppose->d_oppose = newDC;
    }

    return newDC;
}

// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
// sommet (� cr�er) dont les coordonn�es sont celles du point p.
// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(const Point &p, DemiCote* oppose)
{
    Sommet *s = new Sommet{p,nullptr,static_cast<int>(d_tabSommets.size())};
    d_tabSommets.push_back(s);

	DemiCote *newDC = new DemiCote{nullptr, nullptr, oppose, s, static_cast<int>(d_tabDemiCotes.size())};

	s->d_demiCote = newDC;

	newDC->d_suivant = newDC;
	newDC->d_precedent = newDC;

	d_tabDemiCotes.push_back(newDC);

	if( oppose != nullptr)
    {
        oppose->d_oppose = newDC;
    }

    return newDC;
}

void Carte::flip(DemiCote* d)
{
    DemiCote *ds = d->suivant();
    DemiCote *dp = d->precedent();
    ds->d_precedent = dp;
    dp->d_suivant = ds;
    ds->oppose()->suivant()->d_precedent = d;
    ds->suivant()->oppose()->d_suivant = d;
    dp->oppose()->suivant()->d_precedent = d->oppose();
    dp->oppose()->d_suivant = d->oppose();


}
