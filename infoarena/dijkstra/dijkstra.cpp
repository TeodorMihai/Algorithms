#include <bits/stdc++.h>

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

const int INF = 0x3f3f3f3f;
#define pp pair<int, int>
#define x first
#define y second

const int NMAX = 5e4 + 5;

int n, m;
vector<pp> g[NMAX];


void dijkstra(int start) {

	priority_queue<pp , vector<pp>, greater<pp> > pq;
	pq.push({0, start});

	int dist[NMAX];
	memset(dist, 0x3f, sizeof(dist));

	dist[start] = 0;

	while(pq.empty() == false) {

		pp p = pq.top();
		pq.pop();

		int node = p.y;
		int d = dist[node];

		for(pp pe : g[node]) 	
			if(dist[pe.x] > pe.y + d) {

				dist[pe.x] = pe.y + d;
				pq.push({dist[pe.x], pe.x});
			}
	}

	for(int i = 2; i <= n ; ++i)
		if(dist[i] == INF)
			fout << 0 << ' ';
		else 
			fout << dist[i] << ' ';
}

int main() {

	fin >> n >> m ;

	for(int i = 1; i <= m ; ++i) {
		int x, y, c;

		fin >> x >> y >> c;
		g[x].push_back({y, c});
	}

	dijkstra(1);
	return 0;
}