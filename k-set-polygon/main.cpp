#include <iostream>
#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "polygone.h"
#include "sommet.h"
#include <iostream>

using namespace std;



Sommet* fusionConvexes(Sommet* x, Sommet* y)
{
    Sommet* a = x;
    Sommet* b = y;
    //supportant bas
    while (a->precedent()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == -1 || b->suivant()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == -1) {


        //test si le sommet a précédent est à droite de (ab)
        if (a->precedent()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == -1)
        {
            a = a->precedent();
        }

        //test si le sommet b précédent est à droite de (ab)
        if (b->suivant()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == -1)
        {
            b = b->suivant();
        }
    }

    b->setPrecedent(a);
    a->setSuivant(b);

    b = x;
    a = y;
    //supportant haut
    while (a->precedent()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == 0 || b->suivant()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == 0) {


        //test si le sommet a précédent est à droite de (ab)
        if (a->precedent()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == 0)
        {
            a = a->precedent();
        }

        //test si le sommet b précédent est à droite de (ab)
        if (b->suivant()->coordonnees().aGauche(a->coordonnees(), b->coordonnees()) == 0)
        {
            b = b->suivant();
        }
    }

    b->setPrecedent(a);
    a->setSuivant(b);

    return a;
}

int main()
{
    opengraphsize(1800,900);
    setbkcolor(RED);
    cleardevice();
    setcolor(BLUE);

    //Déclaration de points
    Point p1{100,100};
    Point p2{100,500};
    Point p3{500,500};
    Point p4{500,100};

    //Construction d'un polygone
    Polygone poly{};
    Sommet *prec1 = poly.ajouteSommet(p1,nullptr);
    Sommet *prec2 = poly.ajouteSommet(p2,prec1);
    Sommet *prec3 = poly.ajouteSommet(p3,prec2);
    Sommet *prec4 = poly.ajouteSommet(p4,prec3);
    //poly.supprimeSommet(prec3);

    Point p1a{ 150,150 };
    Point p2a{ 150,550 };
    Point p3a{ 550,550 };
    Point p4a{ 550,150 };

    Polygone poly1{};
    Sommet* prec1a = poly1.ajouteSommet(p1a, nullptr);
    Sommet* prec2a = poly1.ajouteSommet(p2a, prec1a);
    Sommet* prec3a = poly1.ajouteSommet(p3a, prec2a);
    Sommet* prec4a = poly1.ajouteSommet(p4a, prec3a);
    
    

    trace(poly);

    getch();
    closegraph();
}

