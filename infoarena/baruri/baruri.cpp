#include <bits/stdc++.h>

using namespace std;

ifstream fin("baruri.in");
ofstream fout("baruri.out");

const int NMAX = 100009;

int n; int t; int m;

int v[NMAX];
int aib[NMAX];

int bit(int x) { return x & (-x); }

void update(int pos, int val) {

	for( ; pos <= n ; pos += bit(pos))
		aib[pos] += val;
}

int query(int pos) {

	int sum = 0;

	for( ;pos > 0 ; pos -= bit(pos))
		sum += aib[pos];
	
	return sum;
}

void clearAib() {

	for(int i = 1; i <= n; ++i)
		aib[i] = 0, v[i] = 0;
}

void read() {

	fin >> n;

	for(int i = 1; i <= n ; ++i) {
		fin >> v[i];
		update(i, v[i]);
	}

}

void solve() {

	fin >> m;

	while(m--) {

		int type ;
		fin >> type;

		int b1; int b2; int d;

		switch(type) {
			case 0 : fin >> b1 >> d ; fout << query(min ( n, b1 + d) ) - query(b1 - d - 1) - v[b1] << '\n'; break;
			case 1 : fin >> d >> b1 ; update(b1, d); v[b1] += d; break;
			case 2 : fin >> d >> b1 ; update(b1, -d); v[b1] -= d; break;
			case 3 : fin >> d >> b1 >> b2 ; update(b1, -d); update(b2, d); v[b1] -= d; v[b2] += d; break;
		}
	}
}

int main() {


	fin >> t;

	while(t--) {

		read();
		solve();
		clearAib();
	}

	return 0;
}