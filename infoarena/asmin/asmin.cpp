#include <bits/stdc++.h>

using namespace std;

ifstream fin("asmin.in");
ofstream fout("asmin.out");

const int NMAX = 16e3 + 5;
const int KMAX = 1005;
const int INF = 0x3f3f3f3f;
//O(n) vrei o informatie despre fiecare nod, mutat de la nod la la altul
int n, k;

vector<int> g[NMAX];
int v[NMAX];
int computed[NMAX];
int bests = 0x3f3f3f3f;


int add(int node1,int  node2) {

	int s = v[node2] - v[node1];
	if(s < 0)
		s += k;
	return s;
}


int dfs(int node, int fath, int now) {
	
	int s = add(fath, node);

	for(int x : g[node])
		if(x != fath)
			s += dfs(x, node, v[node]);

	return s;
}

void dfs2(int node, int fath) {

	if(node != 1)
		computed[node] = computed[fath] - add(fath, node) + add(node, fath) + v[node] - v[fath];
	
	if(computed[node] < bests)
		bests = computed[node];

	for(int x : g[node])
		if(x != fath)
			dfs2(x, node);
}

int main() {

	fin >> n >> k;
	
	for(int i = 1; i < n ; ++i) {
		int x, y;
		fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	for(int i = 1; i <= n; ++i)
		fin >> v[i];

	computed[1] = dfs(1, 0, 0);
	dfs2(1, 0);
	
	vector<int> sol;

	for(int i = 1; i <= n ; ++i)
		if(computed[i] == bests)
			sol.push_back(i);

	fout << bests << ' ' << sol.size() << '\n';

	for(int x : sol)
		fout << x << ' ';

	fout << '\n';
	
	
	return 0;
}