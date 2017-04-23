#include <bits/stdc++.h>

using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int NMAX = 5e4 + 5;

int n, m;
int viz[NMAX];
vector<int> g[NMAX];
int ord[NMAX];

void dfs(int node) {

	viz[node] = 1;

	for(int x : g[node])
		if(viz[x] == 0)
			dfs(x);

	ord[++ord[0]] = node;
}

int main() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {

		int x, y; fin >> x >> y;
		g[x].push_back(y);
	}

	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0)
			dfs(i);

	for(int i = ord[0] ; i > 0 ; --i)
		fout << ord[i] << ' ';

	return 0;
}