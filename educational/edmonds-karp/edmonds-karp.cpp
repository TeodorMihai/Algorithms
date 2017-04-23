#include <bits/stdc++.h>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int NMAX = 1005;
const int INF = 0x3f3f3f3f;

int n, m;

int s, d;

int rez[NMAX][NMAX];
int pre[NMAX];

vector<int> g[NMAX];

int totalFlow;

void read() {

	fin >> n >> m;

	s = 1;
	d = n;

	for(int i = 1; i <= m; ++i) {
		int x, y, cap;
		fin >> x >> y >> cap;
		rez[x][y] = cap;
		g[x].push_back(y);
		g[y].push_back(x);
	}

}

bool bfs(int s, int d) {

	queue<int> q;
	bool viz[NMAX]; 
	memset(viz, 0, sizeof(viz));
	viz[s] = true;
	q.push(s);
	pre[s] = s;

	while(q.empty() == false) {

		int node = q.front();
		q.pop();

		if(node == d) continue;

		for(int x : g[node])
			if(rez[node][x] > 0 && viz[x] == false) {
				viz[x] = true;

				q.push(x);
				pre[x] = node;
			}
	}

	return viz[d];

}

void solve() {

	while(bfs(s, d) == true) {

		for(int x : g[d]) {

			int flow = INF;
			pre[d] = x;

			for(int y = d; y != pre[y]; y = pre[y])
				flow = min(flow, rez[pre[y]][y]);

			for(int y = d; y != pre[y]; y = pre[y]) {
				rez[pre[y]][y] -= flow;
				rez[y][pre[y]] += flow;
			}

			totalFlow += flow;
		}

	}

	fout << totalFlow << '\n';
 
}

int main() {

	read(); solve();

	return 0;
}