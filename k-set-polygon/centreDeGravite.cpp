#include "centreDeGravite.h"



using namespace std;

void CentreDeGravite::affiche() const{
	
	circle(x() / t_ensemble.size(), y() / t_ensemble.size(), 2);
	cout << "Les points du tableau du centre de gravité x = " << x()<< " et y = "<< y()<<" sont "<< taille() << " : \n";
	for (Point a : t_ensemble) {
		cout << "x = " << a.x() << " et y = " << a.y() << "\n";
	}
}

