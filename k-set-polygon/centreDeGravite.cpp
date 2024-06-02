#include "centreDeGravite.h"
#include "polygone.h"


using namespace std;

CentreDeGravite::CentreDeGravite(vector<int> tab) : Point(), t_ensemble() {
	int xActuel = 0;
	int yActuel = 0;
	for (const auto i : tab) {
		xActuel += Polygone::d_tous[i].x();
		yActuel += Polygone::d_tous[i].y();
	}
	setX(xActuel);
	setY(yActuel);
}

void CentreDeGravite::affiche() const {

	//circle(x() / t_ensemble.size(), y() / t_ensemble.size(), 2);
	cout << "Les points du tableau du centre de gravité x = " << x()<< " et y = "<< y()<<" sont : \n";
	cout << "x = " << x() << " et y = " << y() << "\n";
	
}
void CentreDeGravite::affiche(int k) const {

	circle(x() / k, 1000-( y() / k), 2);
}
