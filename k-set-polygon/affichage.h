﻿#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "sommet.h"
#include "polygone.h"
#include "centreDeGravite.h"
#include "graphics.h"
#include <iostream>
#include <vector>
#include <algorithm>


// trace un segment entre deux points a et b
void segment1(const CentreDeGravite& a, const CentreDeGravite& b);

void segment(const CentreDeGravite& a, const CentreDeGravite& b, int k);

// trace le polygone P dans une fen�tre graphique
void trace(const Polygone& P);

void trace1(const Polygone& P);

//Sommet* fusionConvexes(Sommet* x, Sommet* y);

#endif
