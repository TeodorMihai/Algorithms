#include <bits/stdc++.h>

using namespace std;

ifstream fin("fmcm.in");
ofstream fout("fmcm.out");

const int NMAX = 355;
const int INF = 0x3f3f3f3f;

int n, m, s, d;
int prev1[NMAX];
int rez[NMAX][NMAX];
int cost[NMAX][NMAX];
vector<int> g[NMAX];
int totalFlow, minCost;

void read() {

	fin >> n >> m >> s >> d;
	for(int i = 1; i <= m ; ++i) {
		int x, y, c, z;
		fin >> x >> y >> c >> z;
		//capacitatea c si costul z
		g[x].push_back(y);
		g[y].push_back(x);
		rez[x][y] = c;
		cost[x][y] = z;
		cost[y][x] = -z;
	}
}

bool bellmanford(int s, int d) {

	queue<int> q;
	int inqueue[NMAX], dist[NMAX];
	memset(inqueue, 0, sizeof(inqueue));
	memset(dist, 0x3f, sizeof(dist));

	q.push(s);
	dist[s] = 0;
	inqueue[s] = 1;

	while(q.empty() == false) {

		int node = q.front();
		inqueue[node] = 0;
		q.pop();

		for(int x : g[node]) 
			if(rez[node][x] > 0 && dist[x] > dist[node] + cost[node][x]) {

				dist[x] = dist[node] + cost[node][x];
				prev1[x] = node;

				if(inqueue[x] == 0) {

					q.push(x);
					inqueue[x] = 1;
				}
			}
	}

	return dist[d] != INF;
}

void solve() {

	while(bellmanford(s, d)) {

		int flow = INF;
		prev1[s] = s;
		for(int i = d; i != prev1[i]; i = prev1[i])
			flow = min(flow, rez[prev1[i]][i]);

		totalFlow += flow;

		for(int i = d; i != prev1[i]; i = prev1[i]) {

			rez[prev1[i]][i] -= flow;
			rez[i][prev1[i]] += flow;
			minCost += flow * cost[prev1[i]][i];
		}
	}

	fout << minCost << '\n';
}

int main() {

	read(); solve();

	return 0;
}