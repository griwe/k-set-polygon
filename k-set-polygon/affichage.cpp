#include "affichage.h"

// trace un segment entre deux points a et b
void segment(const CentreDeGravite& a, const CentreDeGravite& b, int k)
{
    std::cout<< "test :" << a.x() << ","<< a.y()<< "et k est : " << k << std::endl;
    
    if (k != 0)
        line(a.x() / k, a.y() / k, b.x() / k, b.y() / k);

}

void segment1(const CentreDeGravite& a, const CentreDeGravite& b)
{
    int k = a.taille();
    std::cout << "test :" << a.x() << "," << a.y() << "et k est : " << k << std::endl;
    if (k != 0)
        line(a.x() / k, a.y() / k, b.x() / k, b.y() / k);

}

void trace1(const Polygone& P)
{
    setcolor(GREEN);
    Sommet* p = P.getMin();
    if (p == nullptr)
        return;
    do
    {
        segment1(p->cdg(), p->suivant()->cdg());
        p = p->suivant();

    } while (p != P.getMin());
}

// trace le polygone P dans une fenêtre graphique
void trace(const Polygone& P)
{
    setcolor(BLUE);
    Sommet* p = P.getMin();
    vector<int> pActuel = P.getPointsMin();
    CentreDeGravite actuel;
    actuel = CentreDeGravite{ pActuel };

    actuel.affiche();
    cout << "Le tableau pActuel contient : " << endl;
    for (const auto a : pActuel) {
        cout << a << endl;
    }

    if (p == nullptr || pActuel.empty())
    {
        cout << "hmm bizarre"<<endl;
        return;
    }
        

    if (p == p->suivant()) {
        actuel.affiche(pActuel.size());
    }
    else
    {
        CentreDeGravite suivant;
        do
        {
            int i = 0;
            while (i < pActuel.size() && p->enlever() != pActuel[i] ) {
                i = i + 1;
            }
            if (i != pActuel.size()) {
                pActuel[i] = p->suivant()->ajouter();
            }         
            
            suivant = CentreDeGravite{ pActuel };

            segment(actuel, suivant, pActuel.size());
            
            p = p->suivant();
            actuel = suivant;

        } while (p != P.getMin());
    }
   
}





