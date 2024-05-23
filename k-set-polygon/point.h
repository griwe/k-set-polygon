#ifndef POINT_H
#define POINT_H

class Point
{

public:
	// constructeurs
	Point() : d_x{ 0 }, d_y{ 0 } {}
	Point(int x, int y) : d_x{ x }, d_y{ y } {}
	// accesseurs
	int x() const { return d_x; }
	int y() const { return d_y; }
	void setX(int x) { d_x = x; }
	void setY(int y) { d_y = y; }
	// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
	// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
	int aGauche(const Point& a, const Point& b) const;
	bool operator<(const Point& a) const;

	void operator+=(const Point& p);

	void operator-=(const Point& p);

	void affiche() const;

private:
	// coordonn�es
	int d_x, d_y;
};

#endif
