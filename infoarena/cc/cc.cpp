#include <bits/stdc++.h>

using namespace std;

ifstream fin("cc.in");
ofstream fout("cc.out");

const int NMAX = 207;
const int INF = 0x3f3f3f3f;

int n; int s; int d;

int cost[NMAX][NMAX];
int rez[NMAX][NMAX];
int ant[NMAX];

int c;

void read() {

	fin >> n ;
	s = 0;
	d = 2 * n + 1;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			rez[i][j + n] = 1;
			fin >> cost[i][j + n];
			cost[j + n][i] = -cost[i][j + n];
		}
}

bool bf(int s, int d) {

	int dist[NMAX];
	int inf = 0;
	int sup = 2 * n + 1;

	bool inq[NMAX];
	memset(inq, false, sizeof(inq));

	for(int i = inf; i <= sup ; ++i)
		dist[i] = INF;

	inq[s] = true;
	dist[s] = 0;

	queue<int> q;
	q.push(s);

	while(q.empty() == false) {
		int node = q.front();
		q.pop();
		inq[node] = false;

		for(int i = inf; i <= sup; ++i)
			if(dist[i] > dist[node] + cost[node][i] && rez[node][i] > 0) {
				
				if(inq[i] == false) 
					q.push(i);

				inq[i] = true;
				dist[i] = dist[node] + cost[node][i];
				ant[i] = node;
			}
	}

	return dist[d] == INF ? false : true;
}

void solve() {

	for(int i = 1; i <= n; ++i)
		rez[s][i] = 1, rez[i + n][d] = 1;

	while( bf(s, d) ) {
		for(int x = d ; x != s; x = ant[x]) {

			rez[ant[x]][x] -= 1;
			rez[x][ant[x]] += 1;
			c += cost[ant[x]][x];
			//cout << cost[ant[x]][x] << '\n'; 
		}
	}

	fout << c << '\n'; 
}

int main() {

	read();
	solve();
	return 0;
}