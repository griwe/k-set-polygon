#include "polygone.h"
#include "point.h"
#include <iostream>

using namespace std;

// Implémentation des méthodes de la classe Polygone

// destructeur
/**
Polygone::~Polygone()
{
    Sommet* s = d_premier->suivant();
    while (s != d_premier)
    {
        supprimeSommet(s);
        s = d_premier->suivant();
    }
    delete d_premier;
}*/




// Ajoute un nouveau sommet au polygone. Les coordonnées du sommet à ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l’un des sommets déjà présents dans le polygone,
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d’adresse sommetPrecedent.
// Dans le deuxième cas, le nouveau sommet devient l’unique sommet du polygone.
// Dans tous les cas, la méthode renvoie l’adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const CentreDeGravite& p, Sommet* sommetPrecedent)
{
    if (sommetPrecedent == nullptr)
    {
        Sommet* s = new Sommet{ p };
        s->d_suivant = s;
        s->d_precedent = s;

        

        return s;
    }
    else
    {
        Sommet* s = new Sommet{ p,sommetPrecedent->suivant(),sommetPrecedent };

        //s->d_suivant = sommetPrecedent->suivant();
        //s->d_precedent = sommetPrecedent;

        sommetPrecedent->suivant()->d_precedent = s;
        sommetPrecedent->d_suivant = s;

        return s;
    }


}


// Supprime le sommet d’adresse s du polygone.
// On suppose que s est effectivement présent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
    if (s->precedent() == s)
    {
        delete s;
    }
    else
    {
        s->precedent()->setSuivant(s->suivant());
        s->suivant()->setPrecedent(s->precedent());
    }

}


Sommet* Polygone::getMin()
{
    return d_min;
}

Sommet* Polygone::getMax()
{
    return d_max;
}

void Polygone::affiche()
{
    cout << "Min :" << d_min->cdg().x() << " -> suivant " << d_min->suivant()->cdg().x() << " -> suivant " << d_min->suivant()->suivant()->cdg().x() << endl;
    cout << "Max :" << d_max->cdg().x() << " -> suivant " << d_max->suivant()->cdg().x() << " -> suivant " << d_max->suivant()->suivant()->cdg().x() << endl;

}

