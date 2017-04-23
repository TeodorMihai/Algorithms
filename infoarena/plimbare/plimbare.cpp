#include <bits/stdc++.h>

using namespace std;

ifstream fin("plimbare.in");
ofstream fout("plimbare.out");

const int NMAX = 108;

int n; int m;

bool edge[NMAX][NMAX];

vector<int> g[NMAX];
vector<int> gt[NMAX];

int ord[NMAX]; bool viz[NMAX]; bool viz2[NMAX];

int repr[NMAX];

int maxCycle;
vector<int> cycle;

int st[NMAX];

int pos[NMAX];

void read() {

	fin >> n ;
	m = n * (n - 1) / 2;
	for(int i = 1; i <= m ;++i) {
		int x; int y;
		fin >> x >> y;
		edge[x][y] = true;	
		g[x].push_back(y);	
		gt[y].push_back(x);
	}
}

void dfs(int nod) {

	viz[nod] = 1;

	for(int x : g[nod])
		if(viz[x] == false)
			dfs(x);

	ord[++ord[0]] = nod;
}

void kosaraju(int nod, int repres) {

	viz[nod] = true;
	repr[nod] = repres;

	for(int x : gt[nod])
		if(viz[x] == false)
			kosaraju(x, repres);
}

void bkt(int node, int cnt) {

	for(int x : g[node]) {

		if(repr[x] != repr[node]) continue;
		
		if(viz[x] == true && maxCycle < st[0] - pos[x] + 1) {

			maxCycle = st[0] - pos[x] + 1;
			cycle.clear();

			for(int i = pos[x]; i <= st[0]; ++i)
				cycle.push_back(st[i]);
		}
		
		if(viz[x] == true) continue;

		st[++st[0]] = x;
		pos[x] = st[0];
		viz[x] = true;
		bkt(x, cnt + 1);
		st[0]--;
		viz[x] = false;

	}
}

void solve() {

	for(int i = 1; i <= n; ++i)
		if(viz[i] == false)
			dfs(i);

	memset(viz, 0, sizeof(viz));

	for(int i = ord[0] ; i ; i--)
		if(viz[ord[i]] == false) 
			kosaraju(ord[i], ord[i]);
		
	memset(viz, 0, sizeof(viz));

	for(int i = 1; i <= n; ++i)
		if(viz2[ repr[i] ]  == false) {

			viz2[repr[i]] = true;
			st[++st[0]] = i;
			pos[repr[i]] = 1;
			viz[repr[i]] = true;
			bkt(repr[i], 1);
			--st[0];
		}

	fout << maxCycle << '\n';

	for(int x : cycle)
		fout << x << ' ';
		
}

int main() {

	read();
	solve();
	return 0;
}