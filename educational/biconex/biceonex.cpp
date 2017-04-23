#include <bits/stdc++.h>

using namespace std;

ifstream fin("biconex.in");
ofstream fout("biconex.out");

const int NMAX = 100009;

int n; int m;

vector<int> g[NMAX];
int viz[NMAX];

int s[NMAX];
int low[NMAX];
int ind[NMAX];
int discovery;

void read() {

	fin >> n >> m;
	for(int i = 1; i <= m; ++i) {
		int x; int y;
		fin >> x >>  y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs(int node, int father) {

	viz[node] = 1;
	s[++s[0]] = node;
	discovery++;
	ind[node] = discovery;
	low[node] = discovery;

	for(int x : g[node])
		if(viz[x] == 0) {
			dfs(x, node);
			low[node] = min(low[node], low[x]);
		}
		else if(x != father)
			low[node] = min(low[node], low[x]);

	if(low[node] == ind[node]) { //nu pot ajunge mai sus, punct de articulatie

		
	}
}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == 1)
			dfs(i, 0);
}

int main() {

	return 0;
}