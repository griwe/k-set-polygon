#include "fonction.h"
#include"polygone.h"

bool contains(const std::vector<int> vec, const int indice)
{
	return std::find(vec.begin(), vec.end(), indice) != vec.end();
}


int retourneIndice(std::vector<int> a, std::vector<int> b)
{
	for (int i = 0; i < a.size(); i++) {
		if (!contains(b, a[i])) {
			return a[i];
		}
	}
	return -1;
}


bool aGauche(const std::vector<int> points, const Point& a, const Point& b) {
    for (const auto p : points) {
        int det = (b.x() - a.x()) * (Polygone::d_tous[p].y() - a.y()) - (Polygone::d_tous[p].x() - a.x()) * (b.y() - a.y());

        if (det > 0)
        {
            return true;
        }
    }
    return false;
}

bool aDroite(const std::vector<int> points, const Point& a, const Point& b)
{
    for (const auto p : points) {
        int det = (b.x() - a.x()) * (Polygone::d_tous[p].y() - a.y()) - (Polygone::d_tous[p].x() - a.x()) * (b.y() - a.y());

        if (det < 0)
        {
            return true;
        }
    }
    return false;
}


int trouverIndice(const Point& p) {
    for (int i = 0; i < Polygone::d_tous.size(); i++)
    {
        if (Polygone::d_tous[i] == p)
        {
            return i;
        }
    }
    return -1;
}


void genereCdG(const vector<Point>& tableauPoints, int g, int k, CentreDeGravite& cdg, vector<CentreDeGravite>& tableauCdG)
{
    if (k == 0)
        tableauCdG.push_back(cdg);
    else
    {
        for (int i = g; i <= tableauPoints.size() - k; i++)
        {
            cdg += tableauPoints[i];
            cdg.ajouterPoint(trouverIndice(tableauPoints[i])); //je crois que c'est ca
            genereCdG(tableauPoints, i + 1, k - 1, cdg, tableauCdG);
            cdg.pop_back();
            cdg -= tableauPoints[i];
        }
    }
}

vector<CentreDeGravite> genereCdG(const vector<Point>& tableauPoints, int k)
{
    vector<CentreDeGravite> tableauCdG;
    if (k <= 0 || k > tableauPoints.size())
        return tableauCdG;
    long long taille = 1;
    for (int i = tableauPoints.size(); i > tableauPoints.size() - k; i--)
        taille *= i;
    for (int i = 2; i <= k; i++)
        taille /= i;
    tableauCdG.reserve(taille);
    CentreDeGravite cdg{};
    genereCdG(tableauPoints, 0, k, cdg, tableauCdG);
    //    for (int i = 0; i < tableauCdG.size(); i++)
    //        tableauCdG[i].cdg /= k;
    return tableauCdG;
}

vector<Point> aExclure(vector<Point>& vecp, const Point& p)
{
    int i = 0;
    while (i < vecp.size() && !(vecp[i] == p))
    {
        i++;
    }

    vecp[i] = vecp[vecp.size() - 1];
    vecp.pop_back();

    return vecp;
}

vector<Point> readPointsFromFile(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    string line;

    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return points;
    }

    // Skip the first line containing the count
    getline(file, line);

    while (getline(file, line)) {
        replace(line.begin(), line.end(), ',', '.');
        istringstream iss(line);
        float x, y;
        if (!(iss >> x >> y)) {
            cerr << "Error reading line: " << line << endl;
            continue;
        }
        Point point;
        point.setX(static_cast<int>(round(x)));
        point.setY(static_cast<int>(round(y)));
        points.push_back(point);
    }

    file.close();
    return points;
}