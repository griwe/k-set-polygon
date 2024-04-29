#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
    int det = (b.x() - a.x()) * (d_y-a.y()) - (d_x - a.x()) * (b.y() - a.y());

    if(det > 0) //gauche
    {
        return 1;
    }
    else if(det == 0)
    {
        return 0;
    }
    else //droite
    {
        return -1;
    }
}

bool Point::operator<(const Point& a) const
{
    return this->x()<a.x();
}
