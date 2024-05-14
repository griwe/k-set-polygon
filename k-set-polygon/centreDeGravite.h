#include "point.h"
#include <vector>



class CentreDeGravite : public Point
{
public:

    CentreDeGravite() : Point(), t_ensemble() {} // Appel du constructeur par défaut de Point

    // Constructeurs
    CentreDeGravite(int x, int y) : Point(x, y), t_ensemble() {} // Constructeur avec coordonnées

    CentreDeGravite(const Point& p) : Point(p), t_ensemble() {}

    // Méthode pour ajouter un point à l'ensemble
    void ajouterPoint(const Point& p) {
        t_ensemble.push_back(p);
    }

    void affiche() const;

    void pop_back() {
        t_ensemble.pop_back();
    }
    
    std::vector<Point> ensemble() { return t_ensemble; }

private:
	std::vector<Point> t_ensemble;
};

