#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "point.h"
#include "carte.h"

extern const int height;

// trace un segment entre deux points a et b
void segment(const Point &a, const Point &b);

// trace la carte C dans une fen�tre graphique
void trace(const Carte &C);

void triangulation( vector<Point> &T, Carte &C);

#endif
