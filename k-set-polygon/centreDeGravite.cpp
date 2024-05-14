#include "centreDeGravite.h"
#include "graphics.h"
#include <iostream>

using namespace std;

void CentreDeGravite::affiche() const{
	
	circle(this->x() / this->t_ensemble.size(), this->y() / this->t_ensemble.size(), 3);
	cout << "Les points du tableau du centre de gravité x = " << this->x()<< " et y = "<< this->y()<<" sont : \n";
	for (Point a : t_ensemble) {
		cout << "x = " << a.x() << " et y = " << a.y() << "\n";
	}
}

