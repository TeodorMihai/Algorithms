#include <bits/stdc++.h>

using namespace std;

ifstream fin("critice.in");
ofstream fout("critice.out");

const int NMAX = 1002;
const int INF = 0x3f3f3f3f;

#define pp pair<int, int>

int n; int m;

vector<pp> g[NMAX];

vector<int> sol;

int rez[NMAX][NMAX];
int ant[NMAX];
int mark[NMAX];
int s; int d;

void read() {

	fin >> n >> m ;
	s = 1;
	d = n;

	for(int i = 1; i <= m; ++i) {

		int x; int y; int f;
		fin >> x >> y >> f;
		g[x].push_back({y, i});
		g[y].push_back({x, i});
		rez[x][y] += f;
		rez[y][x] += f;
	}

}

bool bfs(int s, int d) {

	queue<int> q;

	bool viz[NMAX];
	memset(viz, 0, sizeof(viz));
	q.push(s);
	viz[s] = true;
	mark[s] = true;

	for( ; q.empty() == false ; q.pop() ) {

		int node = q.front();

		for(pp p : g[node]) {
			int x = p.first;
			if(viz[x] == false && rez[node][x] > 0) {
				ant[x] = node;
				q.push(x);
				viz[x] = true;
				mark[x] = 1;
			}
		}
	}

	return viz[d];
}

void solve() {

	while(bfs(s, d)) {

		for(int i = 1; i <= n ; ++i) {

			if(rez[i][d] > 0) {

				int maxFlow = rez[i][d];

				for(int x = i ; x != s; x = ant[x])
					maxFlow = min(maxFlow, rez[ant[x]][x]);

				if(maxFlow <= 0) continue;

				rez[i][d] -= maxFlow;
				rez[d][i] += maxFlow;

				for(int x = i ; x != s; x = ant[x]) {
					rez[ant[x]][x] -= maxFlow;
					rez[x][ant[x]] += maxFlow;
				}
			}
		}
	}

	memset(mark, 0, sizeof(mark));
	bfs(s, d);
	int mucCritice = 0;

	for(int i = 1; i <= n; ++i)
		for(pp x : g[i])
			if(mark[i] != mark[x.first])
				sol.push_back(x.second);

	sort(sol.begin(), sol.end());

	fout << sol.size() / 2 << '\n';

	for(int i = 0 ; i < sol.size() ; i++)
		if(i % 2 == 0)
			fout << sol[i] << '\n';
}

int main() {

	read(); solve();

	return 0;
}