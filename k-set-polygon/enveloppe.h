#ifndef ENVELOPPE_H
#define ENVELOPPE_H

#include "point.h"
#include "polygone.h"
#include "fonction.h"
#include"sommet.h"
#include <vector>

using namespace std;

Polygone enveloppe(vector<CentreDeGravite> t, int g, int d);

Polygone lier1Sommet(vector<CentreDeGravite> t, int g, int d);

Polygone lier2Sommet(vector<CentreDeGravite> t, int g, int d);

Polygone lier3Sommet(vector<CentreDeGravite> t, int g, int d);

Sommet* fusionConvexes(Sommet* x, Sommet* y);


#endif
