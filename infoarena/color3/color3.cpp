#include <bits/stdc++.h>

using namespace std;

ifstream fin("colorare3.in");
ofstream fout("colorare3.out");

const int NMAX = 1e5 + 5;
const int MOD = 1e9 + 7;

int n; int k; int ans = 1;

vector<int> g[NMAX];

void dfs(int node, int father) {

	int sons = (node == 1) ? 0 : 1;

	for(int i = 0 ; i < g[node].size(); ++i)
		if(g[node][i] != father)  {
			ans = (1ll * ans * (k - sons) ) % MOD;
			sons++;
			dfs(g[node][i], node);
		}
}

int main() {

	fin >> n >> k;

	for(int i = 1; i < n; ++i) {
		int x; int y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}


	dfs(1, 0);
	fout << ans << '\n';

	return 0;
}