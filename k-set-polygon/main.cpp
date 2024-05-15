#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "polygone.h"
#include "sommet.h"


using namespace std;


Sommet* fusionConvexes(Sommet* x, Sommet* y) {
    Sommet* a = x;
    Sommet* b = y;

    //-cout<<"x:"<<x->cdg().x()<<"y :"<<y->cdg().x()<<endl;

    Sommet* a1 = x;
    Sommet* b1 = y;

    if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        a1 = x->precedent();
    }
    if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        b1 = y->suivant();
    }

    //-cout<<"x1:"<<a1->cdg().x()<<"y1 :"<<y->cdg().x()<<endl;

    while (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == -1 ||
        b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == -1) {
        //test si le sommet a précédent est à droite de (ab)
       //     cout<<"ieme iter"<<b->suivant()->cdg().x()<<" "<<a->cdg().x()<<" "<<b->cdg().x()<<endl;
    // cout<<"ieme iter"<<b->suivant()->cdg().aGauche(a->cdg(), b->cdg())<<endl;

        if (a->suivant()->cdg().aGauche(a->cdg(), b->cdg()) == -1)
        {
            a = a->suivant();
        }

        //test si le sommet b précédent est à droite de (ab)
        if (b->precedent()->cdg().aGauche(a->cdg(), b->cdg()) == -1)
        {
            b = b->precedent();
        }
    }

    //-cout<<"a:"<<a->cdg().x()<<"b :"<<b->cdg().x()<<endl;
  //cout<<"ieme iter"<<b->suivant()->cdg().aGauche(a->cdg(), b->cdg())<<endl;

    //Lien du Bas

    while (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1 || b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
        if (a1->precedent()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
            a1 = a1->precedent();
        }
        if (b1->suivant()->cdg().aGauche(a1->cdg(), b1->cdg()) == 1) {
            b1 = b1->suivant();
        }
    }
    //-cout<<"a1:"<<a1->cdg().x()<<"b1 :"<<b1->cdg().x()<<endl;


    b->setSuivant(a);
    a->setPrecedent(b);

    //Lien du bas
    a1->setSuivant(b1);
    b1->setPrecedent(a1);

    return a;
}


Polygone lier2Sommet(vector<CentreDeGravite> t, int g, int d)
{
    Polygone poly{};
    Sommet* minn = poly.ajouteSommet(t[g], nullptr);
    Sommet* maxx = poly.ajouteSommet(t[d], minn);

    poly.setMin(minn);
    poly.setMax(maxx);

    setcolor(BLUE);
    trace(poly);
    getch();

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
    }
    else if (t[d].aGauche(t[g], t[g + 1]) == 1)
    {
        Sommet* minn = poly.ajouteSommet(t[g], nullptr);
        Sommet* maxx = poly.ajouteSommet(t[d], minn);
        Sommet* s1 = poly.ajouteSommet(t[g + 1], maxx);

        poly.setMin(minn);
        poly.setMax(maxx);
    }
    setcolor(BLUE);
    trace(poly);
    getch();

    return poly;

}

Polygone enveloppe(vector<CentreDeGravite> t, int g, int d) {
    cout << g << " : " << d << endl;
    int diff = d - g;

    if (diff > 2) {
        int milieu = abs((g + d) / 2);
        Polygone p = Polygone{ enveloppe(t,g,milieu) };

        p.affiche();

        Polygone p1 = Polygone{ enveloppe(t, milieu + 1, d) };

        p1.affiche();


        setcolor(GREEN);
        fusionConvexes(p.getMax(), p1.getMin());
        cout << "--------------"<< p.getMin()->cdg().taille();
       
        Polygone pf = Polygone{ p.getMin(),p1.getMax() };
        trace(pf);
        getch();
        pf.affiche();

        return pf;

    }
    else if (diff == 1) {
        Polygone poly{};
        Sommet* minn = poly.ajouteSommet(t[g], nullptr);
        Sommet* maxx = poly.ajouteSommet(t[d], minn);

        poly.setMin(minn);
        poly.setMax(maxx);

        setcolor(BLUE);
        trace(poly);
        getch();

        return poly;

        //return lier2Sommet(t, g, d);

    }
    else if (diff == 2) {
        return lier3Sommet(t, g, d);
    }
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
            cdg.ajouterPoint(tableauPoints[i]); //je crois que c'est ca
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

void diviserPourRegner(vector<Point> points, int g, int d, int k) {
    int diff = d - g;

    if (diff <= k + 1) {
        vector<Point> slice(points.begin() + g, points.begin() + d + 1);
        vector<CentreDeGravite> tab = genereCdG(slice, k);
        std::sort(tab.begin(), tab.end());
        for (const auto& cdg : tab)
        {
            std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
            cdg.affiche();
        }
        enveloppe(tab, 0, tab.size() - 1);
    }
    else {
        int milieu = abs((g + d) / 2);

        if (k % 2 == 0) {
            diviserPourRegner(points, g, milieu + (abs(k / 2))-1, k);
            diviserPourRegner(points, milieu - (abs(k/2))+1, d, k);

            vector<Point> slice(points.begin() + g, points.begin() + d + 1);
            vector<CentreDeGravite> tab = genereCdG(slice, k);
            std::sort(tab.begin(), tab.end());
            for (const auto& cdg : tab)
            {
                std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
                cdg.affiche();
            }
            enveloppe(tab, 0, tab.size() - 1);
        }
        else {
            diviserPourRegner(points, g, milieu +abs( k / 2), k);
            diviserPourRegner(points, milieu - abs(k/2) -1 , d, k);

            vector<Point> slice(points.begin() + g, points.begin() + d + 1);
            vector<CentreDeGravite> tab = genereCdG(slice, k);
            std::sort(tab.begin(), tab.end());
            for (const auto& cdg : tab)
            {
                std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
                cdg.affiche();
            }
            enveloppe(tab, 0, tab.size() - 1);
        }
        
    }
}

void test1()
{
    //  d'un générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
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
    diviserPourRegner(points, 0, points.size()-1, 2);

    /*
    int k = 2;
    vector<CentreDeGravite> tab = genereCdG(points, k);

    // Tri du vector par ordre croissant des coordonnées x
    std::sort(tab.begin(), tab.end());
    setcolor(BLUE);
    // Affichage des points
    std::cout << "Points ordonnés par ordre croissant de leurs coordonnées x : \n";
    for (const auto& cdg : tab)
    {
        std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
        cdg.affiche();
    }
    getch();
    */
    //enveloppe(tab, 0, tab.size() - 1);
}

int main()
{
    

    opengraphsize(2500, 1500);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLUE);

    test1();


    getch();
    closegraph();


    /**
    //Déclaration de points
    Point p1{200,100};
    Point p2{100,500};
    Point p3{350,500};
    Point p4{500,100};//plus a droite

    //Construction d'un polygone
    Polygone poly{};
    Sommet *prec1 = poly.ajouteSommet(p1,nullptr);
    Sommet *prec2 = poly.ajouteSommet(p2,prec1);
    Sommet *prec3 = poly.ajouteSommet(p3,prec2);
    Sommet *prec4 = poly.ajouteSommet(p4,prec3);
    //poly.supprimeSommet(prec3);

    Point p1a{ 550,150 };//plus a gauche
    Point p2a{ 670,220 };
    Point p3a{ 950,250 };
    Point p4a{ 970,150 };

    Polygone poly1{};
    Sommet* prec1a = poly1.ajouteSommet(p1a, nullptr);
    Sommet* prec2a = poly1.ajouteSommet(p2a, prec1a);
    Sommet* prec3a = poly1.ajouteSommet(p3a, prec2a);
    Sommet* prec4a = poly1.ajouteSommet(p4a, prec3a);
    
    

    trace(poly);
    trace(poly1);
    



    getch();
    setcolor(YELLOW);


    trace(Polygone{ fusionConvexes(prec4, prec1a) });
    **/
    
   
}

