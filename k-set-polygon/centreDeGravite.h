#ifndef CENTREDEGRAVITE_H
#define CENTREDEGRAVITE_H



#include "point.h"
#include <vector>
#include "graphics.h"
#include <iostream>
#include <vector>




class CentreDeGravite : public Point
{
public:

    CentreDeGravite() : Point(), t_ensemble() {} // Appel du constructeur par d�faut de Point

    // Constructeurs
    CentreDeGravite(int x, int y) : Point(x, y), t_ensemble() {} // Constructeur avec coordonn�es

    CentreDeGravite(const Point& p) : Point(p), t_ensemble() {}

    CentreDeGravite(std::vector<int> tab);

    //CentreDeGravite(CentreDeGravite& cdg) : Point{ cdg.x(),cdg.y()}, t_ensemble{cdg.ensemble()} {}

    // M�thode pour ajouter un point � l'ensemble
    void ajouterPoint(int indice) {t_ensemble.push_back(indice);}

    void affiche() const;

    void affiche(int k) const;

    void pop_back() {t_ensemble.pop_back();}

    std::vector<int> ensemble() const { return t_ensemble; }

    int taille() const { return t_ensemble.size(); }

private:
    std::vector<int> t_ensemble;

};

#endif
