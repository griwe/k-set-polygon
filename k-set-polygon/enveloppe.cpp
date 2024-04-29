#include "enveloppe.h"
#include "point.h"
#include "polygone.h"
#include <iostream>

#include <vector>

using namespace std;


// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P)
{
	Polygone poly{};

    Sommet *s1 = poly.ajouteSommet(a,nullptr);
    Sommet *s2 = poly.ajouteSommet(b,s1);

    if(c.aGauche(a,b) == 1) // s'il est a gauche il doite etre place apres b (pour que le dans le triangle quand on navigue sur les usivant on tourne dans le sens trigo)
    {
        Sommet *s3 = poly.ajouteSommet(c,s2);
        std::cout<<"ici";
        return s3;
    }
    else // s'il est a droite il doite etre place apres a (pour que le dans le triangle quand on navigue sur les usivant on tourne dans le sens trigo)
    {
        Sommet *s3 = poly.ajouteSommet(c,s1);
        std::cout<<"here";
        return s3;
    }
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(vector<Point>&T, Polygone &P)
{
}
