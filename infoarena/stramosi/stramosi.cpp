#include <bits/stdc++.h>

using namespace std;

ifstream fin("stramosi.in");
ofstream fout("stramosi.out");

const int NMAX = 25e4 + 5;

int n; int m;

vector<int> g[NMAX];

int ancestor[19][NMAX];
int lg[NMAX];

int main() {

	fin >> n >> m;
	for(int i = 1; i <= n ; ++i) {
		int x; fin >> x;
		ancestor[0][i] = x;
	}

	lg[1] = 0;
	lg[0] = 0;

	for(int i = 2; i <= n ; ++i)
		lg[i] = lg[i / 2] + 1;

	for(int i = 1; i <= lg[n]; ++i)
		for(int j = 1; j <= n; ++j)
			ancestor[i][j] = ancestor[i - 1][ ancestor[i - 1][j] ];

	while(m--) {
		int p; int q;
		//al p-lea stramos al lui q
		fin >> q >> p;
		if(p > n) {
			fout << 0 << '\n';
			continue;
		}

		while(q > 0 && p > 0) {
			q = ancestor[lg[p]][q];
			p -= (1 << lg[p]);
		}

		fout << q << '\n';
	}

	return 0;
}