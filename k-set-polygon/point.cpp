#include "point.h"
#include "graphics.h"

// renvoie 1, -1 ou 0 selon que le point auquel la méthode est appliquée est
// à gauche de, à droite de, ou sur la droite (ab) orientée de a vers b.
int Point::aGauche(const Point& a, const Point& b) const
{
    int det = (b.x() - a.x()) * (d_y - a.y()) - (d_x - a.x()) * (b.y() - a.y());

    if (det > 0)
    {
        return 1;
    }
    else if (det == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


bool Point::operator<(const Point& a) const
{
    return d_x < a.x();
}

bool Point::operator==(const Point& a) const
{
    return (d_x == a.x() && d_y == a.y());
}

void Point::operator+=(const Point& p)
{
    d_x += p.x();
    d_y += p.y();
}

void Point::operator=(const Point& p)
{
    d_x = p.x();
    d_y = p.y();
}

void Point::operator-=(const Point& p)
{
    d_x -= p.x();
    d_y -= p.y();
}

void Point::affiche() const
{
    circle(d_x,1000- d_y, 3);

}

