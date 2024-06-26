﻿#ifndef SOMMET_H
#define SOMMET_H

#include "centreDeGravite.h"
#include "point.h"
#include<vector>
#include<iterator>
#include <algorithm>
#include"fonction.h"
using namespace std;


class Sommet
{
	friend class Polygone;
public:
	// Constructeur par d�faut
	Sommet() : d_suivant(nullptr), d_precedent(nullptr), d_ajouter(-1), d_enlever(-1) {}

	// Constructeur � partir d'un point p
	/*Sommet(const Point& p, Sommet* suivant = nullptr, Sommet* precedent = nullptr, Point* ajouter = nullptr, Point* enlever = nullptr)
		: d_cdg{ CentreDeGravite(p) }, d_suivant{ suivant }, d_precedent{ precedent }, d_ajouter(ajouter), d_enlever(enlever) {}
	*/
	Sommet(const CentreDeGravite& p, Sommet* suivant = nullptr, Sommet* precedent = nullptr)
		: d_cdg{ p }, d_suivant{ suivant }, d_precedent{ precedent }, d_ajouter(-1), d_enlever(-1) {}

	//Sommet(const CentreDeGravite& cdg) : d_cdg(cdg), d_suivant(nullptr), d_precedent(nullptr), d_ajouter(nullptr), d_enlever(nullptr) {}

	//Sommet(const CentreDeGravite& cdg, Sommet* suivant, Sommet* precedent, Point* ajouter, Point* enlever) : d_cdg(cdg), d_suivant(suivant), d_precedent(precedent), d_ajouter(ajouter), d_enlever(enlever) {}

	Sommet(const Sommet& s) : d_cdg(s.cdg()), d_suivant(s.suivant()), d_precedent(s.precedent()), d_ajouter(s.ajouter()), d_enlever(s.enlever()) {}

	// accesseurs
	CentreDeGravite cdg() const { return d_cdg; }
	Sommet* suivant() const { return d_suivant; }
	Sommet* precedent() const;
	int ajouter() const { return d_ajouter; }
	int enlever() const { return d_enlever; }
	void setSuivant(Sommet* suivant);
	void setPrecedent(Sommet* precedent);
	void setAjouter(int ajouter);
	void setEnlever(int enlever);

	
	void inialiserAjEnl();


private:
	// constructeur � partir d'un point p

	// destructeur vide priv�
	//~Sommet() = default;

	// coordonn�es
	CentreDeGravite d_cdg; // on veut pas savoir ca
	// sommets suivant et precedent
	Sommet* d_suivant, * d_precedent;
	int d_ajouter, d_enlever; //calculer les coordonnées 
};

#endif


