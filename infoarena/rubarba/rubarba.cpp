//nu imparti niciodata la 0!! pune INF-initul definit de tine
#include <bits/stdc++.h>

using namespace std;

ifstream fin("rubarba.in");
ofstream fout("rubarba.out");

const int NMAX = 100009;
const long double eps = 1e-12;
const long double pi = M_PI;
const long double INF = 1e20;
typedef long double ld;

int n; int start; int head;

struct Point2d {

	long double x;
	long double y;

	Point2d() : x(0) , y(0) { }
	Point2d(long double _x , long double _y) : x(_x), y(_y) {}
};

struct Point3d {

	long double x;
	long double y;
	long double z;

	Point3d() : x(0) , y(0), z(0) { }
	Point3d(long double _x , long double _y, long double _z) : x(_x), y(_y) , z(_z) {}
};


struct Line {

	long double a; 
	long double b;
	long double c;

	Line() {}
	Line(long double _a, long double _b, long double _c) : a(_a), b(_b), c(_c) { }
};

Point2d v[NMAX];
Point2d s[NMAX];

//p1 p2 cos
long double dotProduct2d(Point2d p1, Point2d p2) {

	return p1.x * p2.x + p1.y * p2.y;
}

long double dotProduct3d(Point3d p1, Point3d p2) {

	return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

//   i  j  k
//p1 x1 y1 z1
//p2 x2 y2 z2
//p1 p2 sin 
Point3d crossProduct3d(Point3d p1, Point3d p2) {

	long double x = p1.y * p2.z - p1.z * p2.y;
	long double y = -p1.x * p2.z + p1.z * p2.x;
	long double z = p1.x * p2.y - p1.y * p2.x;

	return Point3d(x, y, z);
}

long double det2d(Point2d p1, Point2d p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

long double det3d(Point3d p1, Point3d p2, Point3d p3) {

	return dotProduct3d(crossProduct3d(p1, p2) , p3); 
}

long double triangleArea(Point2d p1, Point2d p2, Point2d p3) {

	Point3d p31(p1.x, p1.y, 1.0);
	Point3d p32(p2.x, p2.y, 1.0);
	Point3d p33(p3.x, p3.y, 1.0);

	return det3d(p31, p32, p33) * 0.5;
}


bool equals(long double x, long double y) {

	return fabs(x - y) < eps;
}

long double angle(Point2d p1, Point2d p2) {

	return atan2(p2.y - p1.y , p2.x - p1.x);
}

long double angle0_2pi(Point2d p1, Point2d p2) {
	long double u = angle(p1, p2);
	return u < 0 ? u + 2 * pi : u;
}

long double dist(Point2d p1, Point2d p2) {

	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

Line findEq(Point2d p1, Point2d p2) {

	return Line(p1.y - p2.y, p2.x - p1.x, p1.x * p2.y - p1.y * p2.x);
}

Line findOpEq(Point2d p1, Point2d p2) {

	Point2d p = Point2d( (p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
	long double m;
	if(p1.y == p2.y)
		m = -INF;
	else 
		m = -1.0 / ((p1.y - p2.y) / (p1.x - p2.x));
	//vrem ecuatia dreptei cu punctul p si dreapta m
	return Line(-m, 1, m * p.x - p.y);
}

Line findEqP(Point2d p1, Point2d p2) {

	long double m ;
	if(p1.x == p2.x)
		m = INF;
	else 
		m = (p1.y - p2.y) / (p1.x - p2.x);
	return Line( m , p1.y - m * p1.x, 0);
}

Line findOpEqP(Point2d p1, Point2d p2) {
	long double m;
	if(p1.x == p2.x)
		m = INF ;
	else 
		m = (p1.y - p2.y) / (p1.x - p2.x);
	if(m == 0)
		m = -INF;
	else 
		m = -1.0 / m;

	Point2d p( (p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0 );
	return Line( m , p.y - m * p.x, 0);
}

long double distHP(Point2d p, Line l) {
	return (p.y - l.a * p.x - l.b) / sqrt(1.0 + l.a * l.a);
}

long double distH(Point2d p, Line l) {

	return (l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

void read() {

	fin >> n;

	start = 1;

	for(int i = 1; i <= n ; ++i)  {
		fin >> v[i].x >> v[i].y;

		if(v[i].x < v[start].x)
			start = i;
		else if( v[i].x == v[start].x && v[i].y < v[start].y)
			start = i;
	}

}

struct cmp {

	bool operator()(const Point2d& p1, const Point2d& p2) {
		long double m1 = (p1.y - v[1].y) / (p1.x - v[1].x);
		long double m2 = (p2.y - v[1].y) / (p2.x - v[1].x);
		if(equals(m1, m2))
			return dist(v[1], p1) < dist(v[1], p2);
		return m1 < m2;
	}

} cmpU;


void grahamScan() {

	s[++head] = v[1];
	s[++head] = v[2];

	for(int i = 3; i <= n; ++i) {

		while(head >= 2 && triangleArea(s[head - 1], s[head], v[i]) <= 0)
			head--;
		
		s[++head] = v[i];
	}
}

void convexHull() {

	swap(v[1], v[start]);

	sort(v + 2, v + n + 1, cmpU);

	grahamScan();
}

void solve() {

	convexHull();

	if(head <= 1) {
		fout << 0 << '\n';
		exit(0);
	}

	s[head + 1] = s[1];

	long double sur = INF;
	for(int i = 1; i <= head; ++i) {

		//cout << s[i].x << ' ' << s[i].y << '\n';
		Line l1 = findEq(s[i], s[i + 1]);
		Line l2 = findOpEq(s[i], s[i + 1]);
		long double horizontal = 0;
		long double pos = 0;
		long double neg = 0;

		for(int j = 1; j <= head; ++j) {
			
			long double h = fabs(distH(s[j], l1));

			if(h > horizontal)
				horizontal = h;

			h = distH(s[j], l2);
			if(h > pos) pos = h;
			if(h < neg) neg = h;
		}

		if(sur > (long double) horizontal * (pos - neg))
			sur = (long double) horizontal * (pos - neg);
	}

	fout << fixed << setprecision(2) << sur << '\n';
}

int main() {

	read(); solve(); 

	return 0;
}