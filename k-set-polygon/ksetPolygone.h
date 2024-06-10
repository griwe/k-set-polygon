#ifndef KSETPOLYGONE_H
#define KSETPOLYGONE_H
#include<vector>
#include"fonction.h"
#include"enveloppe.h"
#include"polygone.h"
#include"sommet.h"
#include"point.h"
#include"centreDeGravite.h"
#include"affichage.h"

using namespace std;

Polygone fusionConvexeKset(Polygone g, Polygone d, int cg, int cd);

Polygone Base(const vector<Point>& p1, int g, int d);

Polygone diviserPourRegner(vector<Point> points, int g, int d, int k, int profondeur, int& compteur);


#endif
