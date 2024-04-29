#include <iostream>
#include <random>
#include <ctime>

#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "carte.h"

using namespace std;
const int height = 900;



int main()
{
    opengraphsize(1800, height);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLUE);
    /*
    Point p2{100,100};
    Point p1{100,500};

    Point p3{500,500};
    Point p4{500,100};

    Carte c = Carte{};
    DemiCote *d = c.ajouteCote(p1,p2);
    DemiCote *d1 = c.ajouteCote(p3,p4);
    DemiCote *d2 = c.ajouteCote(d,d1);
    DemiCote *d3 = c.ajouteCote(d->oppose(),d1->oppose());
    */
    // Initialisation du générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(std::time(0));


    // Création du vecteur pour stocker les points
    std::vector<Point> points;

    // Générer 10 points aléatoires et les stocker dans le vecteur
    for (int i = 0; i < 10; i++) {
        std::uniform_int_distribution<int> dis(100, 800);
        int x = dis(gen);
        int y = dis(gen);
        points.push_back(Point(x, y));
    }
    Carte c = Carte{};

    triangulation(points, c);



    //c.ajouteCote(p2,p3);
    //c.ajouteCote(p1,p4);

    trace(c);

    getch();
    closegraph();
}

