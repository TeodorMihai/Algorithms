#include <bits/stdc++.h>

using namespace std;

const int NMAX = 105;

int n; int m;

vector<int> g[NMAX];

char s[NMAX * 30]; bool used[NMAX];

int pairL[NMAX]; int pairR[NMAX];

int c[NMAX];

int com = 0;

void parsare(char *s) {

	int len = strlen(s);

	int i = 0;

	vector<int> v;

	while(i < len) {

		int nr = 0;

		while(i < len && (s[i] == ' ' || s[i] == '\n')) ++i;

		while(i < len && '0' <= s[i] && s[i] <= '9') nr = nr * 10 + s[i] - '0', ++i;
		if(nr)
			v.push_back(nr);
	}

	if(v.size() > 0)
		com++;

	for(int i = 0 ; i < v.size(); ++i) 
		g[v[i]].push_back(com);
}

void read() {

	scanf("%d%d", &n, &m);

	while(fgets(s, NMAX * 30, stdin)) 
		parsare(s);
}

bool dfs(int node) {

	if(used[node] == true) return false;

	used[node] = true;

	for(int x : g[node]) 
		if(pairR[x] == 0) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	for(int x : g[node])
		if(dfs( pairR[x] )) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	return false;
}

void solve() {	

	int cuplaj = 0;

	for(int i = 1; i <= n ; ++i)
		if(pairL[i] == 0)
			if(dfs(i))
				cuplaj++;
			else {
				memset(used, 0, sizeof(used));
				cuplaj += dfs(i);
			}

	if(cuplaj != m)
		cout << 0 << '\n';
	else 
		for(int i = 1; i <= m; ++i)
			cout << pairR[i] << '\n'; 
}

int main() {

	freopen("senat.in", "r", stdin);
	freopen("senat.out", "w", stdout);

	read();

	solve();

	return 0;
}