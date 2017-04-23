//se adauga un nod fictiv pentru a face graful eulerian,
//in los sa se elimine muchii
#include <bits/stdc++.h>

using namespace std;

ifstream fin("fotbal2.in");
ofstream fout("fotbal2.out");

const int NMAX = 50009;


struct Edge {
	int x;
	int ind;
	int dir;

	Edge(int _x, int _ind, int _dir) : x(_x), ind(_ind), dir(_dir) { }
};

int n; int m;

vector<Edge> g[NMAX];

int degree[NMAX];
int win[NMAX * 2];
int viz[NMAX * 2];

int last = 0;
int cnt;

void read() {

	fin >> n >> m;

	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back({y, i, 1});
		g[y].push_back({x, i, 0});
		degree[x]++;
		degree[y]++;
	}
}

void euler(int node) {

	for(Edge p : g[node]) {

		int x = p.x;
		int edge = p.ind;

		if(viz[edge] == 0) {
			viz[edge] = 1;
			euler(x);
		}
	}

	if(node != 0 && last != 0)
		for(Edge p : g[last])
			if(p.x == node && win[p.ind] == 0) {
				win[p.ind] = last;
				cnt++;
				break;
			}

	last = node;
}

int main() {

	read();

	bool imp = false;

	for(int i = 1; i <= n; ++i)
		if(degree[i] % 2 == 1) {
			imp = true;
			g[i].push_back({0, m + i, 1});
			g[0].push_back({i, m + i, 0});
		}

	for(int i = 1; i <= n; ++i) {
		if(cnt < m) {
			last = i;
			euler(i);
		}
	}

	if(imp)
		fout << 2 << "\n";
	else 
		fout << 0 << '\n';

	for(int i = 1; i <= m; ++i)
		fout << win[i] << '\n'; 

	return 0;
}