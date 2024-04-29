#include <iostream>
#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "polygone.h"
#include <iostream>

using namespace std;


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
    poly.supprimeSommet(prec3);

    trace(poly);

    getch();
    closegraph();
}

