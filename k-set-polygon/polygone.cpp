#include "polygone.h"
#include "point.h"

using namespace std;

// Impl�mentation des m�thodes de la classe Polygone

// destructeur
Polygone::~Polygone()
{
    Sommet *s = d_premier->suivant();
    while(s != d_premier)
    {
		supprimeSommet(s);
		s=d_premier->suivant();
	}
	delete d_premier;
}

// Ajoute un nouveau sommet au polygone. Les coordonn�es du sommet � ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l�un des sommets d�j� pr�sents dans le polygone,
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d�adresse sommetPrecedent.
// Dans le deuxi�me cas, le nouveau sommet devient l�unique sommet du polygone.
// Dans tous les cas, la m�thode renvoie l�adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const Point &p, Sommet* sommetPrecedent)
{
    if(sommetPrecedent == nullptr)
    {
        Sommet *s = new Sommet{p};
        s->d_suivant = s;
        s->d_precedent = s;

        d_premier = s;

        return s;
    }
    else
    {
        Sommet *s = new Sommet{p,sommetPrecedent->suivant(),sommetPrecedent};

        //s->d_suivant = sommetPrecedent->suivant();
        //s->d_precedent = sommetPrecedent;

        sommetPrecedent->suivant()->d_precedent = s;
        sommetPrecedent->d_suivant = s;

        return s;
    }


}


// Supprime le sommet d�adresse s du polygone.
// On suppose que s est effectivement pr�sent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
    if(s->precedent() == s)
    {
        delete s;
    }
    else
    {
        s->precedent()->d_suivant = s->suivant();
        s->suivant()->d_precedent = s->precedent();
    }

}



