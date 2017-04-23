#include <bits/stdc++.h>

using namespace std;

ifstream fin("resturi.in");
ofstream fout("resturi.out");

const int NMAX = 32;

int n; 

int p[NMAX]; int r[NMAX];

int euler(int a, int b, int& x, int& y) {

	//a * x + b * y = gcd(a, b) stim a si b

	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}

	int x0, y0;
	int d = euler(b , a % b, x0, y0);
	//stim: b* x0 + (a % b) * y0 = d
	//vrem: a * x + b * y = d
	x = y0;
	y = (d - a * x) / b;
	return d;
}

pair<int, int> findSol(int p1, int r1, int p2, int r2) {

	//x == r1 mod p1
	//x == r2 mod p2, find x

	//exista m1, m2 ai m1 * p1 + m2 * p2 = 1, bezout identity gcd(p1, p2) = 1
	int m1, m2;

	euler(p1, p2, m1, m2);
	//r1 * m2 * p2 + r2 * p1 * m1

	int r = (1ll * r1 * m2 * p2 + 1ll * r2 * p1 * m1) % (1ll * p1 * p2);
	if(r < 0)
		r += p1 * p2;

	return make_pair(r, p1 * p2);
}

int main() {

	int t ; fin >> t;

	while(t--) {

		fin >> n;

		for(int i = 1; i <= n ; ++i)
			fin >> p[i] >> r[i];

		for(int i = 2; i <= n ; ++i) {

			pair<int, int> pp = findSol(p[i - 1], r[i - 1], p[i], r[i]);
			r[i] = pp.first;
			p[i] = pp.second;
		}

		fout << r[n] << '\n';
	}

	return 0;
}