#include <bits/stdc++.h>

using namespace std;

ifstream fin("lanterna.in");
ofstream fout("lanterna.out");

const int NMAX = 52;
const int MAXW = 1002;
const int INF = 0x3f3f3f3f;

#define pp pair<int,int>

int n; int m; int k;

struct Edge {

	int nod;
	int tm;
	int w;
	Edge() { }
	Edge(int _nod, int _tm, int _w) : nod(_nod) , tm(_tm), w(_w) { }
};

vector<Edge> g[NMAX];

int dist[NMAX][MAXW];//timpul cel mai bund e a ajunge in nodul i cu j watti

int fri[NMAX];

void read() {

	fin >> n >> k;
	
	for(int i = 1; i <= n; ++i) 
		fin >> fri[i];
	fin >> m;
	for(int i = 1; i <= m; ++i) {
		int a; int b; int t; int w;
		fin >> a >> b >> t >> w;
		g[a].push_back({b, t, w});
		g[b].push_back({a, t, w});
	}
}

int bf(int watti) {

	queue<Edge> q;

	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= watti; ++j)
			dist[i][j] = INF;

	dist[1][0] = 0;
	q.push({1, 0, 0});

	while(q.empty() == false) {

		int nod = q.front().nod;
		int tm = q.front().tm;
		int w = q.front().w;

		q.pop();

		for(Edge x : g[nod]) {	

			int c = w + x.w;
			
			if(watti < c) continue;

			if(fri[x.nod] == 1 && dist[x.nod][0] > dist[nod][w] + x.tm) {
				dist[x.nod][0] = dist[nod][w] + x.tm;
				q.push({x.nod, dist[x.nod][0], 0});
			}

			if(fri[x.nod] == 0 && dist[x.nod][c] > dist[nod][w] + x.tm) {
				dist[x.nod][c] = dist[nod][w] + x.tm;
				q.push({x.nod, dist[x.nod][c], c});
			}
		}
	}	

	int mini = INF;

	for(int i = watti ; i >= 0 ; --i) 
		if(dist[n][i] < mini)
			mini = dist[n][i];

	return mini;
}

void solve() {

	int step; int pos;
	for(step = 1; step <= k; step <<= 1);

	int target = bf(k);
	
	fout << target << ' '; 

	for(pos = 0; step ; step >>= 1)
		if(pos + step < k && bf(pos + step) > target)
			pos += step;

	fout << pos + 1 << '\n'; 
}

int main() {

	read();
	solve();
	return 0;
}
