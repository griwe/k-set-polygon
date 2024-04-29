#include "affichage.h"
#include "point.h"
#include "polygone.h"
#include "graphics.h"
#include <iostream>


// trace un segment entre deux points a et b
void segment(const Point & a, const Point & b)
{
    line(a.x(), a.y(), b.x(), b.y());
}


// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P)
{
    Sommet *p = P.premier();

     if(p==nullptr)
        return;

    do
    {
        segment(p->coordonnees(), p->suivant()->coordonnees());
        p = p->suivant();

    }while(p !=  P.premier());
}





