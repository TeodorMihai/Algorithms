#include <bits/stdc++.h>

using namespace std;

ifstream fin("inundatii.in");
ofstream fout("inundatii.out");

const int NMAX = 5e4 + 4;
typedef long long ll;
struct Point {

	int x, y, z;
	Point() { }
	Point(int x, int y, int z) : x(x), y(y), z(z) { }
};


int n;
Point v[NMAX];

int get(int ind, int lvl) {

	if(lvl == 0)
		return v[ind].x;
	else if(lvl == 1)
		return v[ind].y;
	else if(lvl == 2)
		return v[ind].z;
}

ll compute(int x, int lvl) {

	
	ll s = 0;	
	for(int i = 1; i <= n; ++i)
		s += 1ll * abs(get(i, lvl) - get(x, lvl));

	if(n % 2 == 1) {
		int y = (n - 1) / 2;
		s += 1ll * y * (y + 1);
	} else {

		s += 1ll * n / 2;
		int y = (n - 2) / 2;
		s += 1ll * y * (y + 1);
	}

	return s;
}

int tsearch(int st, int dr, int lvl) {

	if(st == dr) return st;
	if(dr == st - 1) 
		return compute(dr, lvl) > compute(st, lvl) ? st : dr;

	int mleft = st + (dr - st) / 3;
	int mright = st + 2 * (dr - st) / 3;

	if(compute(mleft, lvl) > compute(mright, lvl))
		return tsearch(mleft + 1, dr, lvl);
	else 
		return tsearch(st, mright, lvl);


}

int main() {

	fin >> n;
	
	for(int i = 1; i <= n ; ++i)
		fin >> v[i].x >> v[i].y >> v[i].z;
	fout << compute(tsearch(1, n, 0), 0) + compute(tsearch(1, n, 1), 1) + compute(tsearch(1, n, 2), 2) << '\n';
	return 0;
}