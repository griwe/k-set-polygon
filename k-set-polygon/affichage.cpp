#include "affichage.h"
#include "point.h"
#include "carte.h"
#include "graphics.h"
#include <iostream>
#include <algorithm>
using namespace std;


// trace un segment entre deux points a et b
void segment(const Point & a, const Point & b)
{
    line(a.x(), height - a.y(), b.x(), height - b.y());
}

void trace(const Carte &C)
{
    for(int i=0; i<C.nbDemiCotes(); i++)
    {
       DemiCote *dc = C.demiCote(i);
       Point p1 = dc->coordonnees();

       DemiCote *dcOp = dc->oppose();
       Point p2 = dcOp->coordonnees();

       segment(p1,p2);
    }


}

void triangulation( vector<Point> &T, Carte &C)
{
    sort(T.begin(),T.end()); //on suppose que l’opération < est surchargé pour les points
    DemiCote *dc = C.ajouteCote(T[1],T[0]) ;
    for(int i = 2 ; i < T.size(); i++)
    {
        DemiCote* loin = C.ajouteCote(T[i],dc);
        while(loin->coordonnees().aGauche( dc->coordonnees() , dc->suivant()->suivant()->oppose()->coordonnees()) == -1)
              {
                   dc = C.ajouteCote(dc->suivant()->suivant()->oppose(),loin);
                   dc = dc->precedent();
              }
        dc = loin->oppose()->precedent();
        while(loin->coordonnees().aGauche(dc->coordonnees(), dc->oppose()->coordonnees()) == 1 )
            {
                loin = C.ajouteCote(loin, dc->oppose()->precedent());// loin = C.ajouteDemiCote( mettre les paramatres dans le bon sens)
                dc = dc->oppose()->precedent()->precedent();
            }
        dc = loin;
    }
}
