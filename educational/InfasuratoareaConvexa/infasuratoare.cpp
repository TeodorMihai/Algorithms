#include <bits/stdc++.h>

using namespace std;

ifstream fin("infasuratoare.in");
ofstream fout("infasuratoare.out");

const int NMAX = 120009;
const double eps = 1e-12;
const double pi = M_PI;

int n; int start; int head;

struct Point2d {

	double x;
	double y;

	Point2d() : x(0) , y(0) { }
	Point2d(double _x , double _y) : x(_x), y(_y) {}
};

struct Point3d {

	double x;
	double y;
	double z;

	Point3d() : x(0) , y(0), z(0) { }
	Point3d(double _x , double _y, double _z) : x(_x), y(_y) , z(_z) {}
};

Point2d v[NMAX];
Point2d s[NMAX];


//p1 p2 cos
double dotProduct2d(Point2d p1, Point2d p2) {

	return p1.x * p2.x + p1.y * p2.y;
}

double dotProduct3d(Point3d p1, Point3d p2) {

	return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

//   i  j  k
//p1 x1 y1 z1
//p2 x2 y2 z2
//p1 p2 sin 
Point3d crossProduct3d(Point3d p1, Point3d p2) {

	double x = p1.y * p2.z - p1.z * p2.y;
	double y = -p1.x * p2.z + p1.z * p2.x;
	double z = p1.x * p2.y - p1.y * p2.x;

	return Point3d(x, y, z);
}

double det2d(Point2d p1, Point2d p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

double det3d(Point3d p1, Point3d p2, Point3d p3) {

	return dotProduct3d(crossProduct3d(p1, p2) , p3); 
}

double triangleArea(Point2d p1, Point2d p2, Point2d p3) {

	Point3d p31(p1.x, p1.y, 1.0);
	Point3d p32(p2.x, p2.y, 1.0);
	Point3d p33(p3.x, p3.y, 1.0);

	return det3d(p31, p32, p33) * 0.5;
}


bool equals(double x, double y) {

	return fabs(x - y) < eps;
}

double angle(Point2d p1, Point2d p2) {

	return atan2(p2.y - p1.y , p2.x - p1.x);
}

double angle0_2pi(Point2d p1, Point2d p2) {
	double u = angle(p1, p2);
	return u < 0 ? u + 2 * pi : u;
}

double dist(Point2d p1, Point2d p2) {

	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
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
		return (p1.y - v[1].y) / (p1.x - v[1].x) < (p2.y - v[1].y) / (p2.x - v[1].x);
	}
} cmpU;


void grahamScan() {

	s[++head] = v[1];
	s[++head] = v[2];

	for(int i = 3; i <= n; ++i) {

		while(head >= 2 && triangleArea(s[head - 1], s[head], v[i]) < eps)
			head--;
		
		s[++head] = v[i];
	}
}

void convexHull() {

	swap(v[1], v[start]);

	sort(v + 2, v + n + 1, cmpU);

	grahamScan();
}

void print() {

	fout << head << '\n';
	fout << fixed << setprecision(10);

	for(int i = 1; i <= head; ++i)
		fout << s[i].x << ' ' << s[i].y << '\n'; 
}

int main() {

	read(); convexHull(); print();

	return 0;
}