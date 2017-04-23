#include <bits/stdc++.h>

using namespace std;

ifstream fin("tribut.in");
ofstream fout("tribut.out");

const int NMAX = 205;
const int INF = 0X3F3F3F3F;

int n; int m; int s; int d;

int rez[NMAX][NMAX];

vector<int> g[NMAX];
int ant[NMAX];

void read() {

	fin >> n >> m;
	s = 0;
	d = n + m + 1;
	for(int i = 1; i <= n; ++i) {

		int x;
		fin >> x;
		g[s].push_back(i);
		g[i].push_back(s);
		rez[s][i] = x;
		rez[i][s] = 0;
	}

	for(int i = 1; i <= m; ++i) {

		int p; int sum;
		fin >> p >> sum;
		g[i + n].push_back(d);
		g[d].push_back(i + n);
		rez[i + n][d] = sum;

		for(int j = 1; j <= p ; ++j) {
			int x; fin >> x;
		
			g[x].push_back(n + i);
			g[n + i].push_back(x);
			rez[x][n + i] = rez[s][x];
			rez[n + i][x] = 0;
		}
	}
}

bool bfs(int s, int d) {

	bool viz[NMAX];

	memset(viz, 0, sizeof(viz));
	queue<int> q;
	q.push(s);
	viz[s] = true;

	while(q.empty() == false) {

		int node = q.front();
		q.pop();

		for(int x : g[node])
			if(viz[x] == false && rez[node][x] > 0) 
				viz[x] = true, q.push(x), ant[x] = node;
	}

	return viz[d];
}

int solve() {

	int flow = 0;

	while( bfs(s, d) ) {

		int maxFlow = INF;

		for(int x = d ; x != s; x = ant[x])
			maxFlow = min(maxFlow, rez[ant[x]][x]);

		for(int x = d; x != s; x = ant[x]) {
			rez[ant[x]][x] -= maxFlow;
			rez[x][ant[x]] += maxFlow;
		}

		flow += maxFlow;
	} 

	return flow;
}

void clear() {

	for(int i = s ; i <= d; ++i) {
		g[i].clear();
		for(int j = s; j <= d; ++j)
			rez[i][j] = 0;
	}

}

int main() {

	int t;
	fin >> t;
	while(t--) {
		read();
		fout << solve() << '\n';
		clear();
	}
}