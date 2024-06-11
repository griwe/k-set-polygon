#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "graphics.h"
#include "point.h"
#include "affichage.h"
#include "polygone.h"
#include "sommet.h"
#include "fonction.h"
#include"ksetPolygone.h"
#include <tuple>

using namespace std;

int main()
{
    opengraphsize(2500, 1000);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLUE);
    /*
    //  d'un g n rateur de nombres al atoires
    std::random_device rd;
    std::mt19937 gen(22223);//12345
    std::uniform_int_distribution<> dis(50, 800);

    //  d'un vector de points
    std::vector<Point> points;

    // Remplissage du vector avec 16 points
    for (int i = 0; i < 8; ++i)
    {
        points.emplace_back(dis(gen), dis(gen));
    }
    setcolor(RED);
    
    */

    std::vector<Point> points;
    points = readPointsFromFile("points.txt");
    setcolor(BLUE);
    std::sort(points.begin(), points.end());

    for (const auto& point : points) {

        point.affiche();
    }
    getch();

    Polygone p{};
    p.initPoints(points);
    int compteur = 0;
    //Polygone a = Polygone{ diviserPourRegner(Polygone::d_tous, 0, 6, 4, 0, compteur) };
    //Polygone b = Polygone{ diviserPourRegner(Polygone::d_tous, 0, 12, 4, 0, compteur) };
    //fusionConvexeKset(a, b, 5, 8);
    cout << "Nombre de sommets calculés total : " << compteur << endl;
    getch();

    


    trace(diviserPourRegner(Polygone::d_tous, 0, 12, 4, 0, compteur));
    getch();
    closegraph();
}






























































