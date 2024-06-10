#ifndef FONCTION_H
#define FONCTION_H
#include<vector>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>

#include"point.h"
#include"centreDeGravite.h"
#include"graphics.h"


using namespace std;


bool contains(const std::vector<int> vec, const int indice);

int retourneIndice(std::vector<int> a, std::vector<int> b);

bool aGauche(const std::vector<int> points, const Point& a, const Point& b);

bool aDroite(const std::vector<int> points, const Point& a, const Point& b);

int trouverIndice(const Point& p);

void genereCdG(const std::vector<Point>& tableauPoints, int g, int k, CentreDeGravite& cdg, std::vector<CentreDeGravite>& tableauCdG);

std::vector<CentreDeGravite> genereCdG(const vector<Point>& tableauPoints, int k);

std::vector<Point> aExclure(std::vector<Point>& vecp, const Point& p);

vector<Point> readPointsFromFile(const string& filename);

#endif