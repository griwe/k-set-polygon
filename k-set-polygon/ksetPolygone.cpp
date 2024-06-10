#include "ksetPolygone.h"



Polygone fusionConvexeKset(Polygone g, Polygone d, int cg, int cd) {
    Sommet* actuelG = g.getMax(), * actuelD = d.getMin();
    vector<int> nonCommunD, nonCommunG;
    nonCommunD.push_back(retourneIndice(d.getPointsMin(), g.getPointsMax()));

    nonCommunG.push_back(retourneIndice(g.getPointsMax(), d.getPointsMin()));
    
    //sens de la montée 
     while ((actuelG != g.getMin() && aDroite(nonCommunD, Polygone::d_tous[actuelG->enlever()], Polygone::d_tous[actuelG->suivant()->ajouter()])) ||
        (actuelD != d.getMax() &&  aGauche(nonCommunG, Polygone::d_tous[actuelD->ajouter()], Polygone::d_tous[actuelD->precedent()->enlever()]))) {

        //polygone de gauche
        while (actuelG != g.getMin() &&  aDroite(nonCommunD, Polygone::d_tous[actuelG->enlever()], Polygone::d_tous[actuelG->suivant()->ajouter()])) {
            actuelG = actuelG->suivant();
            if(actuelG->ajouter()<cg && !contains(nonCommunG, actuelG->ajouter()))
                nonCommunG.push_back(actuelG->ajouter());
        }

        //polygone de droite
        while (actuelD != d.getMax() && aGauche(nonCommunG, Polygone::d_tous[actuelD->ajouter()], Polygone::d_tous[actuelD->precedent()->enlever()])) {
            actuelD = actuelD->precedent();
            if (actuelD->enlever() > cd && !contains(nonCommunD, actuelD->enlever()))
                nonCommunD.push_back(actuelD->enlever());
        }
    }
    Sommet* hautG = actuelG, * hautD = actuelD;
    actuelG = g.getMax();
    actuelD = d.getMin();
    nonCommunD.clear();
    nonCommunG.clear();
    nonCommunD.push_back(retourneIndice(d.getPointsMin(), g.getPointsMax()));
    nonCommunG.push_back(retourneIndice(g.getPointsMax(), d.getPointsMin()));
    //sens de la descente
    while ((actuelG != g.getMin() && aGauche(nonCommunD, Polygone::d_tous[actuelG->ajouter()], Polygone::d_tous[actuelG->precedent()->enlever()])) ||
        (actuelD != d.getMax() && aDroite(nonCommunG, Polygone::d_tous[actuelD->enlever()], Polygone::d_tous[actuelD->suivant()->ajouter()]))) {

        //polygone de gauche
        while (actuelG != g.getMin() && aGauche(nonCommunD, Polygone::d_tous[actuelG->ajouter()], Polygone::d_tous[actuelG->precedent()->enlever()])) {
            actuelG = actuelG->precedent();
            if (actuelG->enlever() < cg && !contains(nonCommunG, actuelG->enlever()))
                nonCommunG.push_back(actuelG->enlever());
        }

        //polygone de droite
        while (actuelD != d.getMax() && aDroite(nonCommunG, Polygone::d_tous[actuelD->enlever()], Polygone::d_tous[actuelD->suivant()->ajouter()])) {
            actuelD = actuelD->suivant();
            if (actuelD->ajouter() > cd && !contains(nonCommunD, actuelD->ajouter()))
                nonCommunD.push_back(actuelD->ajouter());
        }
    }
    
    Sommet* basG = actuelG, * basD = actuelD;
    setcolor(RED);
    circle(hautG->cdg().x() / 2, 1000 - (hautG->cdg().y() / 2), 6);
    setcolor(GREEN);
    circle(hautD->cdg().x() / 2, 1000 - (hautD->cdg().y() / 2), 6);
    setcolor(YELLOW);
    circle(basG->cdg().x() / 2, 1000 - (basG->cdg().y() / 2), 6);
    setcolor(BROWN);
    circle(basD->cdg().x() / 2, 1000 - (basD->cdg().y() / 2), 6);
    setcolor(BLUE);
    return Polygone{};
}







Polygone Base(const vector<Point>& p1, int g, int d)
{
    vector<CentreDeGravite> p;
    for (int i = 0; i < p1.size(); i++)
    {
        p.push_back(p1[i]);
    }

    Polygone enveloppeConvexe = Polygone{};
    enveloppeConvexe = enveloppe(p, g, d);

    Sommet* crt = enveloppeConvexe.getMin();
    Sommet* prec = nullptr;

    Polygone kset = Polygone{};

    do
    {
        //Solution temporaire
        vector<Point> slice(p1.begin() + g, p1.begin() + d + 1);
        vector<Point> vec = aExclure(slice, crt->cdg());
        vector<int> indice;

        for (int i = 0; i < vec.size(); i++)
        {
            indice.push_back(trouverIndice(vec[i]));
        }

        CentreDeGravite c = CentreDeGravite{ indice };
        /////////////////////////
        prec = kset.ajouteSommet(c, prec);

        prec->setEnlever(trouverIndice(crt->suivant()->cdg())); //chercher l'indice du point courant dans le tableau tous
        prec->setAjouter(trouverIndice(crt->precedent()->cdg())); //chercher l'indice du point precedent dans le tableau tous

        if (crt == enveloppeConvexe.getMin())
        {
            kset.setMax(prec);
            kset.setTMax(indice);
        }
        else if (crt == enveloppeConvexe.getMax())
        {
            kset.setMin(prec);
            kset.setTMin(indice);
        }

        crt = crt->suivant();
    } while (crt != enveloppeConvexe.getMin());

    return kset;

}

Polygone diviserPourRegner(vector<Point> points, int g, int d, int k, int profondeur, int& compteur) {

    Polygone p1 = Polygone{};
    Polygone p2 = Polygone{};
    Polygone P;

    if (!(d - g <= k))
    {
        int milieu = (g + d) / 2;

        if (k % 2 == 0) {
            int f = profondeur + 1;
            //p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2), k, f, compteur));
            p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2) - 1, k, f, compteur));
            p2.ConstructRecopie(diviserPourRegner(points, milieu - (k / 2) + 1, d, k, f, compteur));
        }
        else {
            int f = profondeur + 1;
            p1.ConstructRecopie(diviserPourRegner(points, g, milieu + (k / 2), k, f, compteur));
            p2.ConstructRecopie(diviserPourRegner(points, milieu - (k / 2) + 1, d, k, f, compteur));
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
        P = enveloppe(tab, 0, tab.size() - 1);
        P.inialiserAjEnlP();
        P.setTMin(P.getMin()->cdg().ensemble());
        P.setTMax(P.getMax()->cdg().ensemble());


    }
    else
    {
        if (d - g == k) {//n = k + 1
            P = Base(points, g, d);
            trace(P);

        }
        else if (d - g == k - 1) { //n = k
            //lier un sommet avec lui même et en faire un polygone
            setcolor(profondeur);
            vector<Point> slice(points.begin() + g, points.begin() + d + 1);
            vector<CentreDeGravite> tab = genereCdG(slice, k);
            std::sort(tab.begin(), tab.end());
            for (const auto& cdg : tab)
            {
                //std::cout << "Point (" << cdg.x() << ", " << cdg.y() << ")\n";
                cdg.affiche();
            }
            P = enveloppe(tab, 0, tab.size() - 1);
            P.inialiserAjEnlP();
            P.setTMin(P.getMin()->cdg().ensemble());
            P.setTMax(P.getMax()->cdg().ensemble());
        }
    }

    Sommet* p = P.getMin();
    do
    {
        cout << "L'indice du point a enlever est : " << p->enlever() << endl;
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




    /*trace1(P);
    getch();*/
    trace(P);
    getch();

    int q = 0;

    return P;
}