#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "sommet.h"
#include "polygone.h"
#include "centreDeGravite.h"
#include "graphics.h"
#include <iostream>


// trace un segment entre deux points a et b
void segment(const CentreDeGravite & a, const CentreDeGravite & b);

// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P);


//Sommet* fusionConvexes(Sommet* x, Sommet* y);

#endif