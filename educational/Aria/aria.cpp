#include <bits/stdc++.h>

using namespace std;

ifstream fin("aria.in");
ofstream fout("aria.out");

const int NMAX = 100009;

int n;

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

void read() {

	fin >> n;
	for(int i = 1; i <= n ; ++i) 
		fin >> v[i].x >> v[i].y;

}

void solve() {

	Point2d p(0, 0);
	double s = 0;

	v[n + 1] = v[1];

	for(int i = 1; i <= n; ++i)
		s += triangleArea(p, v[i], v[i + 1]);

	fout << fixed << setprecision(10) << fabs(s) << '\n';
}

int main() {

	read(); solve();
	return 0;
}