#include <bits/stdc++.h>

using namespace std;

ifstream fin("amenzi.in");
ofstream fout("amenzi.out");

#define pp pair<int, int>
#define x first
#define y second

const int NMAX = 153;
const int TMAX = 3505;
const int INF = 0x3f3f3f3f;

int n, m, k, p;
vector<pp> g[NMAX];
int a[TMAX][NMAX];
//a[i][j] = maximul de amenzi date la momentul i in intersectia j
int amenda[TMAX][NMAX];

void read() {

	fin >> n >> m >> k >> p;

	for(int i = 1; i <= m ; ++i) {
		 int x, y, t;
		 fin >> x >> y >> t;
		 g[x].push_back({y, t});
		 g[y].push_back({x, t});
	}

	for(int i = 1; i <= k ; ++i) {

		int a, b, c; fin >> a >> b >> c;
		amenda[b][a] += c;
	}
}

void solve() {

	for(int i = 0; i < TMAX; ++i)
		for(int j = 1; j <= n; ++j)
			a[i][j] = -1;
	a[0][1] = 0;


	for(int t = 0; t < TMAX; ++t)
		for(int i = 1; i <= n ; ++i) {

			if(t == 0 && i == 1) continue;

			if(t >= 1 && a[t - 1][i] != -1)
				a[t][i] = a[t - 1][i] + amenda[t][i];

			for(pp p : g[i]) {
				if(t >= p.y && a[t - p.y][p.first] != -1)
					a[t][i] = max(a[t][i], a[t - p.y][p.first] + amenda[t][i]);
			}
		}

	for(int i = 1; i <= p ; ++i) {
		int x, t; fin >> x >> t;
		fout << a[t][x] << '\n';
	}
}

int main() {

	read(); solve();
	return 0;
}