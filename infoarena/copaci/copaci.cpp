#include <bits/stdc++.h>

using namespace std;

ifstream fin("copaci.in");
ofstream fout("copaci.out");

typedef long long in64;

#define point pair<in64,in64>
#define x first
#define y second

const int NMAX = 1e5 + 4;

in64 n;
point v[NMAX];

in64 det(point p1, point p2, point p3) {

	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

in64 modul(in64 x) { return x < 0 ? -x : x; }

in64 cmmdc(in64 a, in64 b) {
	return a == 0 ? b : cmmdc(b % a, a);
}

int main() {

	fin >> n;
	
	for(int i = 1; i <= n; ++i)
		fin >> v[i].x >> v[i].y;

	in64 area = 0;

	v[n + 1] = v[1];

	for(int i = 1; i <= n; ++i)
		area += det( point(0, 0), v[i], v[i + 1]);
	//elimina coliniare

	in64 intregi = 0;

	for(int i = 1; i <= n; ++i)
		intregi += cmmdc(modul(v[i + 1].x - v[i].x), modul(v[i + 1].y - v[i].y));

	fout << (modul(area) - intregi) / 2 + 1;

	return 0;
}