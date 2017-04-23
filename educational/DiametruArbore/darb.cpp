#include <bits/stdc++.h>

using namespace std;

ifstream fin("darb.in");
ofstream fout("darb.out");
	
const int NMAX = 1e5 + 5;

int n; int ans;
vector<int> g[NMAX];

int dist[NMAX]; int far;

void read() {

	fin >> n;

	for(int i = 1; i <= n - 1; ++i) {
		
		int x, y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs1(int node, int fath) {

	dist[node] = dist[fath] + 1;
	
	if(dist[far] < dist[node])
		far = node;

	for(int x : g[node])
		if(dist[x] == 0)
			dfs1(x, node);
}

void solve() {

	dfs1(1, 0);
	memset(dist, 0, sizeof(dist));
	dfs1(far, 0);

	fout << dist[far] << '\n';

}

int main() {

	read(); solve();
	return 0;
}