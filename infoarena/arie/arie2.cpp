#include <bits/stdc++.h>

using namespace std;

ifstream fin("arie.in");
ofstream fout("arie.out");

#define x first
#define y second
#define Point pair<double, double>

const int NMAX = 25;
const double MAXC = 1e5;
const double eps = 1e-8;

int n; int m;

Point a[NMAX];
Point b[NMAX];

Point v[NMAX]; int cnt;
Point s[NMAX]; int head;

Point g[NMAX]; int nr;


double areaA;
double areaB;

void read() {

	fin >> n;
	
	for(int i = 1; i <= n; ++i)
		fin >> a[i].x >> a[i].y;

	a[n + 1] = a[1];

	fin >> m;
	
	for(int i = 1; i <= m; ++i)
		fin >> b[i].x >> b[i].y;
	
	b[m + 1] = b[1];
}

bool between(double x1, double x2, double x3) {

	return (x1  - eps <= x2 && x2 <= x3 + eps) || 
		   (x3 - eps <= x2 && x2 <= x1 + eps);
}

double dett(double n1, double n2, double n3, double n4) {
	return n1 * n4 - n2 * n3;
}


double distance(Point p1, Point p2) {
	return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool contains(Point p1, Point p2, Point p3) {

	double d12 = distance(p1, p2);
	double d23 = distance(p2, p3);
	double d13 = distance(p1, p3);
	return fabs(d13 - d12 - d23) < eps;
}

bool intersects(Point p1, Point p2, Point p3, Point p4) {
	//daca segmentul (p1 -> p2) intersecteaza segementul (p3 -> p4)
	double a1 = p1.y - p2.y; double a2 = p3.y - p4.y;
	double b1 = p2.x - p1.x; double b2 = p4.x - p3.x;
	double c1 = p1.x * p2.y - p1.y * p2.x; double c2 = p3.x * p4.y - p3.y * p4.x;

	Point inter;
	double d = dett(a1, b1, a2, b2);

	if(fabs(d) < eps)
		return false;

	inter.x = dett(b1, b2, c1, c2) / d;
    inter.y = dett(a2, c2, a1, c1) / d;

    if(contains(p1, inter, p2) && contains(p3, inter, p4))
    	return true;

   return false;
}

Point intersection(Point p1, Point p2, Point p3, Point p4) {
	//punctul de intersectie, presupuncand ca cele doua seg se intersecteaza
	//daca segmentul (p1 -> p2) intersecteaza segementul (p3 -> p4)
	double a1 = p1.y - p2.y; double a2 = p3.y - p4.y;
	double b1 = p2.x - p1.x; double b2 = p4.x - p3.x;
	double c1 = p1.x * p2.y - p1.y * p2.x; double c2 = p3.x * p4.y - p3.y * p4.x;
	
	Point inter;
	double d = dett(a1, b1, a2, b2);

	inter.x = dett(b1, b2, c1, c2) / d;
    inter.y = dett(a2, c2, a1, c1) / d;

    return inter;
}

double det(Point p1, Point p2, Point p3) {

	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y -
		   p1.y * p2.x - p2.y * p3.x - p3.y * p1.x;
}

bool within(Point p, Point* b, int m, double sur) { 
	//daca punctul p apartine poligonului format din punctele b

	double area = 0;

	for(int i = 1; i <= m ; ++i)
		area += fabs(det(p, b[i], b[i + 1]));
	
	area *= 0.5;

	return fabs(area - sur) < eps;
}

void findWithin() {

	for(int i = 1; i <= n ; ++i) 
		if(within(a[i], b, m, areaB))
			v[++cnt] = a[i];

	for(int i = 1; i <= m; ++i)
		if(within(b[i], a, n, areaA))
			v[++cnt] = b[i];
}

struct cmp {

	bool operator() (const Point& p1, const Point& p2) {
		return det(v[1], p1, p2) < eps;
		//return (p1.y - v[1].y) / (p1.x - v[1].x) > (p2.y - v[1].y) / (p2.x - v[1].x);
	}
} cmpA;


void grahamScan() {

	int piv = 1;
	for(int i = 1; i <= cnt; ++i)
		if(v[piv].x > v[i].x)
			piv = i;
		else if(v[piv].x == v[i].x && v[piv].y > v[i].y)
			piv = i;

	swap(v[1], v[piv]);
	sort(v + 2, v + cnt + 1, cmpA);

	v[cnt + 1] = v[1]; 
	
	g[++nr] = v[1];

	for(int i = 2; i <= cnt; ++i) 
		for(int j = 1; j <= nr; ++j) { 
			if(v[i] == g[j]) break;

			if(j == nr)
				g[++nr] = v[i];
		}
	

	s[++head] = g[1];
	s[++head] = g[2];

	for(int i = 3; i <= nr; ++i) {
		while(head >= 2 && det(s[head - 1], s[head], g[i]) > eps)
			head--;

		s[++head] = g[i];
	}
}

double findSurface() {

	double sur = 0;
	s[head + 1] = s[1];
	for(int i = 1; i <= head; ++i)
		sur += det(Point(0, 0), s[i], s[i + 1]);

	return fabs(sur) * 0.5;
}

void solve() {

	for(int i = 2; i < n; ++i)
		areaA += fabs(det(a[1], a[i], a[i + 1]));

	areaA *= 0.5;

	for(int i = 2; i < m; ++i)
		areaB += fabs(det(b[1], b[i], b[i + 1]));
	areaB *= 0.5;

	findWithin();

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(intersects(a[i], a[i + 1], b[j], b[j + 1]))
				v[++cnt] = intersection(a[i], a[i + 1], b[j], b[j + 1]);

	
	
	if(cnt <= 2) {
		fout << 0 << '\n';
		exit(0);
	}

	grahamScan();
	//cout << head << '\n';

	for(int i = 1; i <= head; ++i)
		cout << s[i].x << ' ' << s[i].y << '\n';
	fout << fixed << setprecision(3) <<  findSurface() << '\n';
}

int main() {

	read();
	solve();
	return 0;
}