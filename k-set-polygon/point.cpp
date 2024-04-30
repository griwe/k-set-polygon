#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la méthode est appliquée est
// à gauche de, à droite de, ou sur la droite (ab) orientée de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
    int det = (b.x()-a.x()) * (d_y - a.y()) - (d_x - a.x()) * (b.y() - a.y());

    if(det > 0)
    {
        return 1;
    }
    else if(det == 0)
    {
        return 0;
    }else
    {
        return -1;
    }
}
