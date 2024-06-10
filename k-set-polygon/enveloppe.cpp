#include "enveloppe.h"
#include "point.h"
#include "polygone.h"
#include <iostream>

#include <vector>

using namespace std;

Sommet* fusionConvexes(Sommet* x, Sommet* y) {
    Sommet* a = x;
    Sommet* b = y;

    Sommet* a1 = x;
    Sommet* b1 = y;

    if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1) {
        a1 = x->precedent();
    }
    if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1) {
        b1 = y->suivant();
    }

    while (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == 1 ||
        b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == 1) {

        if (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == 1) {
            a = a->suivant();
        }
        //test si le sommet b pr c dent est   droite de (ab)
        if (b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == 1) {
            b = b->precedent();
        }
    }
    //Lien du Bas

    while (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1 || b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1) {
        if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1) {
            a1 = a1->precedent();
        }
        if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == -1) {
            b1 = b1->suivant();
        }
    }

    b->setSuivant(a);
    a->setPrecedent(b);

    //Lien du bas
    a1->setSuivant(b1);
    b1->setPrecedent(a1);

    return a;
}

Polygone lier1Sommet(vector<CentreDeGravite> t, int g, int d)
{
    Polygone poly{};
    Sommet* minn = poly.ajouteSommet(t[g], nullptr);

    minn->setSuivant(minn);
    minn->setPrecedent(minn);

    poly.setMin(minn);
    poly.setMax(minn);

    setcolor(BLUE);
    //trace(poly);
    //getch();

    return poly;
}

Polygone lier2Sommet(vector<CentreDeGravite> t, int g, int d)
{
    Polygone poly{};
    Sommet* minn = poly.ajouteSommet(t[g], nullptr);
    Sommet* maxx = poly.ajouteSommet(t[d], minn);

    poly.setMin(minn);
    poly.setMax(maxx);

    setcolor(BLUE);
    //trace(poly);
    //getch();

    return poly;
}

Polygone lier3Sommet(vector<CentreDeGravite> t, int g, int d)
{
    Polygone poly{};
    if (t[d].aGauche(t[g], t[g + 1]) == 1)
    {
        Sommet* minn = poly.ajouteSommet(t[g], nullptr);
        Sommet* s1 = poly.ajouteSommet(t[g + 1], minn);
        Sommet* maxx = poly.ajouteSommet(t[d], s1);

        poly.setMin(minn);
        poly.setMax(maxx);

        //poly.setTMin(minn->cdg().ensemble());
        //poly.setTMax(maxx->cdg().ensemble());
    }
    else if (t[d].aGauche(t[g], t[g + 1]) == -1)
    {
        Sommet* minn = poly.ajouteSommet(t[g], nullptr);
        Sommet* maxx = poly.ajouteSommet(t[d], minn);
        Sommet* s1 = poly.ajouteSommet(t[g + 1], maxx);

        poly.setMin(minn);
        poly.setMax(maxx);

        //poly.setTMin(minn->cdg().ensemble());
        //poly.setTMax(maxx->cdg().ensemble());
    }
    setcolor(BLUE);
    //trace(poly);
    //getch();

    return poly;
}

Polygone enveloppe(vector<CentreDeGravite> t, int g, int d) {
    int diff = d - g;

    if (diff > 2) {
        int milieu = (g + d) / 2;
        Polygone p = Polygone{ enveloppe(t,g,milieu) };
        p.affiche();

        Polygone p1 = Polygone{ enveloppe(t, milieu + 1, d) };
        p1.affiche();

        setcolor(GREEN);
        fusionConvexes(p.getMax(), p1.getMin());

        Polygone pf = Polygone{ p.getMin(),p1.getMax() };
        //trace(pf);
        //getch();
        pf.affiche();
        return pf;
    }
    else if (diff == 1) {
        Polygone pf{};
        Sommet* minn = pf.ajouteSommet(t[g], nullptr);
        Sommet* maxx = pf.ajouteSommet(t[d], minn);

        pf.setMin(minn);
        pf.setMax(maxx);

        setcolor(BLUE);
        //trace(poly);
        //getch();
        return pf;
        //return lier2Sommet(t, g, d);
    }
    else if (diff == 2) {
        return lier3Sommet(t, g, d);
    }
    else if (diff == 0) {
        return lier1Sommet(t, g, d);
    }
}
