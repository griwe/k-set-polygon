#include "affichage.h"

// trace un segment entre deux points a et b
void segment(const CentreDeGravite & a, const CentreDeGravite & b)
{
    int k = a.taille();
    std::cout<< "test :" << a.x() << ","<< a.y()<< "et k est : " << k << std::endl;
    if (k != 0)
        line(a.x() / k, a.y() / k, b.x() / k, b.y() / k);
    
}


// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P)
{
    Sommet *p = P.getMin();

     if(p==nullptr)
        return;

    do
    {
        segment(p->cdg(), p->suivant()->cdg());
        p = p->suivant();

    }while(p !=  P.getMin());
}






