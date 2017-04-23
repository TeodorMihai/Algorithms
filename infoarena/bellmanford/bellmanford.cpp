#include <bits/stdc++.h>

using namespace std;

ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");

#define pp pair<int, int>
#define x first
#define y second

const int NMAX = 5e4 + 5;

int n, m;
int s;
vector<pp> g[NMAX];

void read() {

	fin >> n >> m;
	for(int i = 1; i <= m ; ++i) {
		int x, y, c; fin >> x >> y >> c;
		g[x].push_back({y, c});
	}

	s = 1;
}

void bellmanford() {

	queue<int> q;
	int inqueue[NMAX];
	int dist[NMAX];
	int cntqueue[NMAX];
	bool negativeCycle = false;

	memset(inqueue, 0, sizeof(inqueue));
	memset(cntqueue, 0, sizeof(cntqueue));
	memset(dist, 0x3f, sizeof(dist));

	q.push(s);
	inqueue[s] = 1;
	cntqueue[s] = 1;
	dist[s] = 0;

	while(q.empty() == false && negativeCycle == false) {

		int node = q.front();
		inqueue[node] = 0;

		for(pp p : g[node]) 
			if(dist[p.x] > dist[node] + p.y) {

				dist[p.x] = dist[node] + p.y;

				if(inqueue[p.x] == 0) {

					q.push(p.x);
					inqueue[p.x] = 1;
					cntqueue[p.x]++;

					if(cntqueue[p.x] > n) {
						negativeCycle = true;
						break;
					}
				}
			}

		q.pop();
	}

	if(negativeCycle == true)
		fout << "Ciclu negativ!\n";
	else 
		for(int i = 2; i <= n ; ++i)
			fout << dist[i] << ' ';

}

int main() {

	read(); bellmanford();
	return 0;
}