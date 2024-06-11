#include "polygone.h"
#include "point.h"
#include <iostream>

using namespace std;

std::vector<Point> Polygone::d_tous = std::vector<Point>();

void Polygone::inialiserAjEnlP()
{
    Sommet* m = d_min;
    do
    {
        m->inialiserAjEnl();
        m = m->suivant();
    } while (m != nullptr && m != d_min);
}

// Ajoute un nouveau sommet au polygone. Les coordonn�es du sommet � ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l�un des sommets d�j� pr�sents dans le polygone,
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d�adresse sommetPrecedent.
// Dans le deuxi�me cas, le nouveau sommet devient l�unique sommet du polygone.
// Dans tous les cas, la m�thode renvoie l�adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const CentreDeGravite& p, Sommet* sommetPrecedent)
{
    if (sommetPrecedent == nullptr)
    {
        Sommet* s = new Sommet{ p };
        s->d_suivant = s;
        s->d_precedent = s;



        return s;
    }
    else
    {
        Sommet* s = new Sommet{ p,sommetPrecedent->suivant(),sommetPrecedent };

        //s->d_suivant = sommetPrecedent->suivant();
        //s->d_precedent = sommetPrecedent;

        sommetPrecedent->suivant()->d_precedent = s;
        sommetPrecedent->d_suivant = s;

        return s;
    }
}

// Supprime le sommet d�adresse s du polygone.
// On suppose que s est effectivement pr�sent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
    if (s->precedent() == s)
    {
        delete s;
    }
    else
    {
        s->precedent()->setSuivant(s->suivant());
        s->suivant()->setPrecedent(s->precedent());
    }

}

void Polygone::affiche() const
{
    //cout << "Min :" << d_min->cdg().x() << " -> suivant " << d_min->suivant()->cdg().x() << " -> suivant " << d_min->suivant()->suivant()->cdg().x() << endl;
    //cout << "Max :" << d_max->cdg().x() << " -> suivant " << d_max->suivant()->cdg().x() << " -> suivant " << d_max->suivant()->suivant()->cdg().x() << endl;

}



int Polygone::cptSommet() const
{
    Sommet* s = d_min;
    int i = 0;

    while (s != nullptr && s->suivant() != nullptr && s->suivant() != d_min)
    {
        //cout<< "x: "<<s->cdg().x()<< " , ";
        s = s->suivant();
        i++;
    }
    if (s != nullptr && s->suivant() != nullptr)
    {
        //cout<< "x: "<<s->cdg().x()<< " , ";
        i++;
    }
    return i;
}

std::vector<int> Polygone::sommets() const
{
    Sommet* s = d_min;
    std::vector<int> a;

    while (s != nullptr && s->suivant() != nullptr && s->suivant() != d_min)
    {
        //cout<< "x: "<<s->cdg().x()<< " , ";
        a.push_back(s->cdg().x());
        s = s->suivant();
    }
    if (s != nullptr && s->suivant() != nullptr)
    {
        //cout<< "x: "<<s->cdg().x()<< " , ";
        a.push_back(s->cdg().x());
    }
    return a;
}


int Polygone::trouverNv(const Polygone& p1, const Polygone& p2) const
{
    std::vector<int> a1 = p1.sommets();
    std::vector<int> a2 = p2.sommets();
    std::vector<int> a3 = sommets();
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < a1.size(); i++)
    {
        cout << a1[i] << ",";
    }
    cout << endl;
    for (int i = 0; i < a2.size(); i++)
    {
        cout << a2[i] << ",";
    }
    cout << endl;

    for (int i = 0; i < a3.size(); i++)
    {
        cout << a3[i] << ",";
    }
    cout << endl;
    cout << "-----------------------------------" << endl;


    int k = 0;
    bool t;

    for (int i = 0; i < a3.size(); i++)
    {
        t = true;
        for (int j = 0; j < a1.size(); j++)
        {
            if (a3[i] == a1[j])
            {
                k++;
            }
        }

        for (int j = 0; j < a2.size(); j++)
        {
            if (a3[i] == a2[j])
            {
                k++;
            }
        }

    }
    return (a3.size() - k);
}

void Polygone::initPoints(const std::vector<Point>& pts)
{
    Polygone::d_tous = pts;
}



/*int Polygone::trouverNv2(const Polygone& p1,const Polygone& p2) const
{

  Sommet *s=d_min;
  Sommet *sp1=p1.d_min;
  Sommet *sp2=p2.d_min;

  do
  {
       Sommet *sp1=p1.d_min;
       Sommet *sp2=p2.d_min;

       do
       {
           if(s->cdg().x() == sp1->cdg().x())
           {
               k++;
           }
           sp1=sp1->suivant();
       }
       while(sp1!=nullptr && sp1 != p1.d_min);

       do
       {
           if(s->cdg().x() == sp2->cdg().x())
           {
               k++;
           }
           sp2=sp2->suivant();
       }
       while(sp2!=nullptr &&  sp2 != p2.d_min);

       s=s->suivant();
  }while(s!=nullptr &&  s!=d_min);

   return (a3.size() - k);
}

*/



