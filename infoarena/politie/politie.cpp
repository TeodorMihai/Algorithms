#include <bits/stdc++.h>

using namespace std;

ifstream fin("politie.in");
ofstream fout("politie.out");

const int NMAX = 25e4 + 5;
const int MMAX = 5e5 + 5;

int n; int m; int d; int p;

struct Edge {
	int x; int y; int cat; int cost;
};

Edge e[MMAX];

int t[NMAX];
int h[NMAX];

vector<int> sol;

void read() {

	fin >> n >> m >> d >> p;

	for(int i = 1; i <= m; ++i)
		fin >> e[i].x >> e[i].y >> e[i].cat >> e[i].cost;
}

struct cmp {

	bool operator() (const Edge& a, const Edge& b) {
		if(a.cat == b.cat)
			return a.cost < b.cost;
		return a.cat < b.cat;
	}
} cmp1;


int root(int x) {
	return (t[x] = (t[x] == x ? x : root(t[x])));
}

void unite(int x, int y) {
	
	if( h[x] < h[y] ) 
		t[x] = y;
	else  {
		t[y] = x;
		h[x]++;
	}
}

void solve() {

	sort(e + 1, e + 1 + m, cmp1);

	for(int i = 1; i <= n; ++i)
		t[i] = i, h[i] = 1;

	for(int i = 1; i <= m ; ++i) {

		int x = e[i].x;
		int y = e[i].y;

		if( root(x) != root(y) ) {
			unite( root(x) , root(y) );
			sol.push_back(e[i].cost);
		}
	}

	sort(sol.begin(), sol.end());

	for(int i = sol.size() - 1 ; i >= 0 && p > 0; --i)
		if(i == 0 || sol[i] != sol[i - 1])
			fout << sol[i] << '\n', p--;
}

int main() {

	read();
	solve();
	return 0;
}