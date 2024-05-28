#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "polygone.h"
#include "sommet.h"
#include <tuple>

using namespace std;

Sommet* fusionConvexes(Sommet* x, Sommet* y) {
    Sommet* a = x;
    Sommet* b = y;

    Sommet* a1 = x;
    Sommet* b1 = y;

    if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        a1 = x->precedent();
    }
    if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        b1 = y->suivant();
    }

    while (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == -1 ||
        b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == -1) {

        if (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == -1) {
            a = a->suivant();
        }
        //test si le sommet b pr�c�dent est � droite de (ab)
        if (b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == -1) {
            b = b->precedent();
        }
    }
    //Lien du Bas

    while (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1 || b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
            a1 = a1->precedent();
        }
        if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
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
    if (t[d].aGauche(t[g], t[g + 1]) == -1)
    {
        Sommet* minn = poly.ajouteSommet(t[g], nullptr);
        Sommet* s1 = poly.ajouteSommet(t[g + 1], minn);
        Sommet* maxx = poly.ajouteSommet(t[d], s1);

        poly.setMin(minn);
        poly.setMax(maxx);

        //poly.setTMin(minn->cdg().ensemble());
        //poly.setTMax(maxx->cdg().ensemble());
    }
    else if (t[d].aGauche(t[g], t[g + 1]) == 1)
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

int trouverIndice(const Point& p) {
    for (int i = 0; i < Polygone::d_tous.size(); i++)
    {
        if (Polygone::d_tous[i] == p)
        {
            return i;
        }
    }
    return -1;
}

void genereCdG(const vector<Point>& tableauPoints, int g, int k, CentreDeGravite& cdg, vector<CentreDeGravite>& tableauCdG)
{
    if (k == 0)
        tableauCdG.push_back(cdg);
    else
    {
        for (int i = g; i <= tableauPoints.size() - k; i++)
        {
            cdg += tableauPoints[i];
            cdg.ajouterPoint(trouverIndice(tableauPoints[i])); //je crois que c'est ca
            genereCdG(tableauPoints, i + 1, k - 1, cdg, tableauCdG);
            cdg.pop_back();
            cdg -= tableauPoints[i];

        }
    }
}

vector<CentreDeGravite> genereCdG(const vector<Point>& tableauPoints, int k)
{
    vector<CentreDeGravite> tableauCdG;
    if (k <= 0 || k > tableauPoints.size())
        return tableauCdG;
    long long taille = 1;
    for (int i = tableauPoints.size(); i > tableauPoints.size() - k; i--)
        taille *= i;
    for (int i = 2; i <= k; i++)
        taille /= i;
    tableauCdG.reserve(taille);
    CentreDeGravite cdg{};
    genereCdG(tableauPoints, 0, k, cdg, tableauCdG);
    //    for (int i = 0; i < tableauCdG.size(); i++)
    //        tableauCdG[i].cdg /= k;
    return tableauCdG;
}

Polygone caseDeBaseNEgalK() {
    return Polygone{};
}

Polygone diviserPourRegner(vector<Point> points, int g, int d, int k, int profondeur, int& compteur) {

    Polygone p1 = Polygone{};
    Polygone p2 = Polygone{};

    if (!(d - g <= k))
    {
        int milieu = (g + d) / 2;

        if (k % 2 == 0) {
            int f = profondeur + 1;
            p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2), k, f, compteur));
            //p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2) - 1, k, f, compteur));
            p2.ConstructRecopie(diviserPourRegner(points, milieu - (k / 2) + 1, d, k, f, compteur));
        }
        else {
            int f = profondeur + 1;
            p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2), k, f, compteur));
            p2.ConstructRecopie(diviserPourRegner(points, milieu - (k / 2) + 1, d, k, f, compteur));
        }
    }
    else
    {
        if (d - g == k) {//n = k + 1 

        }
        else if (d - g == k - 1) { //n = k
            //lier un sommet avec lui même et en faire un polygone
        }
    }

    setcolor(profondeur);
    vector<Point> slice(points.begin() + g, points.begin() + d + 1);
    vector<CentreDeGravite> tab = genereCdG(slice, k);
    std::sort(tab.begin(), tab.end());
    for (const auto& cdg : tab)
    {
        //std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
        cdg.affiche();
    }
    Polygone P{ enveloppe(tab, 0, tab.size() - 1) };
    P.inialiserAjEnlP();
    P.setTMin(P.getMin()->cdg().ensemble());
    P.setTMax(P.getMax()->cdg().ensemble());
    Sommet* p = P.getMin();

    do
    {
        cout << "L'indice du point a enlever est : "<<p->enlever()<<endl;
        cout << "L'indice du point a ajouter est : " << p->ajouter() << endl;

        p = p->suivant();

    } while (p != P.getMin());


    cout << "--------------------------------------------------" << endl;
    cout << endl << "Profondeur : " << profondeur << endl;
    cout << "--------------------------------------------------" << endl;
    int i1 = p1.cptSommet();
    int i2 = p2.cptSommet();
    int i3 = P.cptSommet();

    if (i1 == 0) {
        compteur += i3;
        cout << "Construction d'un polygone de " << i3 << " sommets" << endl;
    }
    else {
        compteur += P.trouverNv(p1, p2);
        cout << "Fusion d'un polygone de " << i1 << " sommets et d'un deuxieme de " << i2 << " sommets, resultat : un polygone de " << i3 << " sommets" << endl;
        cout << "Nouveaux sommets generes qui n'existaient pas : " << P.trouverNv(p1, p2) << endl << "--------------------------------------------------" << endl;
    }
    trace1(P);
    getch();
    trace(P);
    getch();

    int q = 0;

    return P;
}

int main()
{
    opengraphsize(2500, 1500);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLUE);

    //  d'un g�n�rateur de nombres al�atoires
    std::random_device rd;
    std::mt19937 gen(12345);
    std::uniform_int_distribution<> dis(50, 800);

    //  d'un vector de points
    std::vector<Point> points;

    // Remplissage du vector avec 16 points
    for (int i = 0; i < 8; ++i)
    {
        points.emplace_back(dis(gen), dis(gen));
    }
    setcolor(RED);
    for (const auto& point : points) {

        point.affiche();
    }
    getch();

    setcolor(BLUE);
    std::sort(points.begin(), points.end());

    Polygone p{};
    p.bricolage(points);
    int compteur = 0;
    Polygone ksetPolygone{ diviserPourRegner(Polygone::d_tous, 0, points.size() - 1, 2, 0, compteur) };
    
    cout << "Nombre de sommets calculés total : " << compteur << endl;
    getch();
    closegraph();
}































































