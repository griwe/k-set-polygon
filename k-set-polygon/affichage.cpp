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
        vector<int> pSuivant = pActuel;
        CentreDeGravite suivant;

        do
        {
            pSuivant.push_back(p->suivant()->ajouter());
            // Trouver l'élément dans le vecteur
            auto it = std::find(pSuivant.begin(), pSuivant.end(), p->enlever());

            // Si l'élément est trouvé, le supprimer
            if (it != pSuivant.end()) {
                pSuivant.erase(it);
            }

            suivant = CentreDeGravite{ pSuivant };

            segment(actuel, suivant, pActuel.size());
            getch();
            p = p->suivant();
            pActuel = pSuivant;
            actuel = suivant;

        } while (p != P.getMin());
    }
   
}





