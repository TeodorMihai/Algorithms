#include <bits/stdc++.h>

using namespace std;

ifstream fin("arie.in");
ofstream fout("arie.out");

const double eps = 1e-12;
const double MAXC = 100.0;//pentru punct in poligon, optional
const int NMAX = 102;

	
struct Point {

	double x;
	double y;

	Point() : x(0) , y(0) { }

	Point(double _x, double _y) : x(_x) , y(_y) { }

	Point operator+(const Point& p) {
		return Point(p.x + x, p.y + y);
	}

	Point operator-(const Point& p) {
		return Point(x - p.x, y - p.y);
	}

	bool operator<(const Point& p) {
		if( fabs(p.x - x) < eps )
			return fabs(p.y - y) < eps ? false : y < p.y;
		return x < p.x;
	}

	bool operator==(const Point& p) {
		return fabs(p.x - x) < eps && fabs(p.y - y) < eps;
	}

	bool operator!=(const Point& p) {
		return !(fabs(p.x - x) < eps && fabs(p.y - y) < eps);
	}

	bool operator>(const Point& p) {
		if( fabs(p.x - x) < eps )
			return fabs(p.y - y) < eps ? false : y > p.y;
		return x > p.x;
	}

	double distance(const Point& p) {
		return sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );
	}

	double det(const Point& p1, const Point& p2) {
		return x * p1.y + p1.x * p2.y + p2.x * y -
			   y * p1.x - p1.y * p2.x - p2.y * x;
	}

	friend ostream& operator<<(ostream& out, const Point& a) {
		out << a.x << ' ' << a.y << '\n';
		return out;
	}

	friend istream& operator>>(istream& in, Point& a) {
		in >> a.x >> a.y;
		return in;
	}
};


struct Line {

	double a;
	double b;
	double c;

	Line() { }
	
	Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) { }

	Line(const Point& p1, const Point& p2) {
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = p1.x * p2.y - p1.y * p2.x;
	}

	/*-1 coincid
	 0 paralele
	 1 se intersecteaza */
	int intersects(const Line& line) {

		double d = a * line.b - b * line.a;

		if(fabs(d) < eps)
			return fabs(c - line.c) < eps ? -1 : 0;

		return 1;
	}
	/* punctul de intersectie dintre cele 2 linii */
	Point intersection(const Line& line) {

		double d = a * line.b - b * line.a;

		if(fabs(d) < eps) //paralele sau coincid
			return Point(0, 0);

		double d1 = b * line.c - c * line.b;
		double d2 = -a * line.c + c * line.a;

		return Point(d1 / d, d2 / d);
	}

	friend ostream& operator<<(ostream& out, const Line& p) {
		out << p.a << ' ' << p.b << ' ' << p.c << '\n';
		return out;
	}
};


struct Segment {

	Point p1;
	Point p2;

	Segment() : p1(0, 0), p2(0, 0) { }
	Segment(Point _p1, Point _p2) : p1(_p1), p2(_p2) { }

	/* punctul p se afla pe segment */
	bool contains(const Point& p) {

		double dAP = p1.distance(p);
		double dBP = p2.distance(p);
		double dAB = p1.distance(p2);

		return fabs(dAB - dAP - dBP) < eps;
	}

	/*segmentul seg intersecteaza segmentul */
	bool intersects(Segment seg) {

		Line l1(p1, p2);
		Line l2(seg.p1, seg.p2);

		if(l1.intersects(l2) == 1) {
			Point inter = l1.intersection(l2);
			if(seg.contains(inter) && this->contains(inter))
				return true;
		}

		return false;
	}

	/*punctul de intersectie intre segmente */
	Point intersection(Segment seg) {

		Line l1(p1, p2);
		Line l2(seg.p1, seg.p2);

		if(l1.intersects(l2) == 1) {
			Point inter = l1.intersection(l2);
			return inter;
		}

		return Point(0, 0);
	}

	friend ostream& operator<<(ostream& out, const Segment& seg) {
		out << seg.p1 << seg.p2;
		return out;
	}
};

struct Poligon {

	vector<Point> v;
	double area;

	Poligon() { }
	/* sortare dupa ceas */
	struct Comparator {

		Point pivot;

		Comparator(Point _pivot) : pivot(_pivot) { }
		
		bool operator()(const Point& p1, const Point&  p2) {
			return pivot.det(p1, p2) < 0;
		}
	};

	/*aria poligonului , merge si daca nu e convex */
	double computeArea() {

		area = 0;

		if(v.size() <= 2)
			return 0;

		v.push_back(v[0]);
		Point p(0, 0);
		
		for(unsigned i = 0; i < v.size() - 1; ++i)
			area += p.det(v[i], v[i + 1]);
		
		v.pop_back();

		area = 0.5 * fabs(area);
		return area;
	}

	//Graham Scan, ordine trigonometrica
	Poligon convexHull() {

		int piv = 0;

		for(unsigned i = 1; i < v.size(); ++i)
			if(v[piv] > v[i])
				piv = i;

		swap(v[piv], v[0]);
		Comparator cmpU(v[0]);

		sort(v.begin() + 1, v.end(), cmpU);

		Poligon pol;

		pol.v.reserve(NMAX);
		
		if(v.size() == 0) return pol;
		pol.v.push_back(v[0]);
		
		if(v.size() == 1) return pol;
		pol.v.push_back(v[1]);

		for(unsigned i = 2; i < v.size() ; ++i) {

			int head = pol.v.size();
			
			while(head >= 2 && pol.v[head - 2].det(pol.v[head - 1], v[i]) > 0)
				pol.v.pop_back(), head--;

			pol.v.push_back(v[i]);
		}

		reverse(pol.v.begin(), pol.v.end());

		return pol;
	}

	/* poligonul contine punctul p, trebuie calculata aria poligonului inainte
	  , merge doar daca poligonul e convex */
	bool contains(Point& p) {

		double sur = 0;

		v.push_back(v[0]);

		for(unsigned i = 0 ; i < v.size() - 1; ++i)
			sur += fabs(p.det(v[i], v[i + 1]));

		v.pop_back();

		sur = fabs(sur) * 0.5;

		return fabs(sur - area) < eps;
	}
	/* netestata */
	bool containsInter(Point& p) {

		Segment seg(p, Point(p.x, MAXC));

		if(v.size() == 0)
			return false;

		v.push_back(v[0]);

		int nrInter = 0;

		for(unsigned i = 0 ; i < v.size() - 1; ++i)
			if(seg.intersects(Segment(v[i], v[i + 1])))
				nrInter++;
		
		v.pop_back();

		return nrInter % 2;
	}

	/*elimina duplicatele, in eroare admisa eps */
	Poligon eliminateDuplicates() {

		Poligon pol;
		if(v.size() == 0) return pol;

		pol.v.reserve(NMAX);
		pol.v.push_back(v[0]);

		for(unsigned i = 0 ; i < v.size(); ++i) 
			for(unsigned j = 0 ; j < pol.v.size(); ++j) {
			
				if(pol.v[j] == v[i]) break;
				
				if(j == pol.v.size() - 1)
					pol.v.push_back(v[i]);
			}

		return pol;
	}

	/* doua poligoane convexe, returneaza poligonul intersectie */
	Poligon intersection(Poligon& pol) {

		Poligon inter;

		pol.computeArea();
		this->computeArea();

		for(unsigned i = 0 ; i < v.size(); ++i)
			if(pol.contains(v[i]))
				inter.v.push_back(v[i]);

		for(unsigned i = 0 ; i < pol.v.size(); ++i)
			if(this->contains(pol.v[i]))
				inter.v.push_back(pol.v[i]);

		v.push_back(v[0]);
		pol.v.push_back(pol.v[0]);

		for(unsigned i = 0 ; i < v.size() - 1; ++i)
			for(unsigned j = 0 ; j < pol.v.size() - 1; ++j) {

				Segment l1 = Segment(v[i], v[i + 1]);
				Segment l2 = Segment(pol.v[j], pol.v[j + 1]);

				if(l1.intersects(l2))
					inter.v.push_back(l1.intersection(l2));
			}

		v.pop_back();
		pol.v.pop_back();

		return inter.eliminateDuplicates().convexHull();
	}

	friend ostream& operator<<(ostream& out, const Poligon pol) {
		
		out << pol.v.size() << '\n';

		out << fixed << setprecision(6);

		for(Point p : pol.v)
			out << p;

		return out;
	}

	friend istream& operator>>(istream& in, Poligon& pol) {

		int n; fin >> n;

		for(int i = 1; i <= n ; ++i) {
			
			Point p; in >> p;
			pol.v.push_back(p);
		}

		return in;
	}
};

int main() {

	Poligon pol1; Poligon pol2;
	fin >> pol1 >> pol2;

	fout << fixed << setprecision(3);
	fout << pol1.intersection(pol2).computeArea() << '\n';

	return 0;
}