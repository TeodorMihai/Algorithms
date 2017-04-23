#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5 + 5;

int n, m, k;

int c[NMAX];
int viz[NMAX];
int cnt[NMAX];

int nodes;

set<int> mul;
vector<int> g[NMAX];

int maxi;

void dfs(int node) {

	nodes++;

	viz[node] = 1;

	cnt[c[node]]++;
	
	if(cnt[c[node]] > maxi)
		maxi = cnt[c[node]];

	mul.insert(c[node]);

	for(int x : g[node])
		if(viz[x] == 0)
			dfs(x);
}

int main() {

	cin >> n >> m >>k;

	for(int i = 1; i <= n ; ++i)
		cin >> c[i];

	for(int i = 1; i <= m ; ++i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	int ans = 0;

	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0) {
			dfs(i);

			for(int x : mul)
				cnt[x] = 0;
			ans += nodes - maxi;
			nodes = 0;
			maxi = 0;
		}

	cout << ans << '\n';



	return 0;
}