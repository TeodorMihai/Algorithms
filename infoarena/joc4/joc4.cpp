//numarul de drumuri disjuncte 
// -dpdv al muchiilor = flux maxim, saturez muchiile
// -dpdv al nodurilor = flux maxim, saturez nodurile, transform un nod intr-o muchie
#include <bits/stdc++.h>

using namespace std;

ifstream fin("joc4.in");
ofstream fout("joc4.out");

#define in16 int16_t
#define uin8 uint8_t

const int NMAX = 502;
const in16 INF = 252;

int n; int m;

vector<in16> g[NMAX];

uin8 rez[NMAX][NMAX];
in16 ant[NMAX];
int s; int d;

void read() {

	fin >> n >> m >> s >> d;

	for(int i = 1; i <= n; ++i) {
		
		g[i].push_back(i + n);
		rez[i][i + n] = 1;

		g[i + n].push_back(i);
		
	}

	for(int i = 1; i <= m; ++i) {
		in16 x; in16 y;
		fin >> x >> y;
		
		// x -> x + n -> y -> y + n 
		//oricand cand pui o muhcie trebuie sa o pui si pe
		//inversa ei ca sa poti retrage fluxul
		g[x + n].push_back(y);
		rez[x + n][y] += 1;
		g[y].push_back(x + n);

		g[y + n].push_back(x);
		rez[y + n][x] += 1;
		g[x].push_back(y + n);		
	}

	//prin s si prind d se poate trece de mai multe ori

	rez[s][s + n] = INF;
	rez[d][d + n] = INF;

	d = d + n;
	n = 2 * n;
}

bool bfs(int s, int d) {

	queue<in16> q;

	bool viz[NMAX];
	memset(viz, 0, sizeof(viz));
	q.push(s);
	viz[s] = true;

	for( ; q.empty() == false ; q.pop() ) {

		int node = q.front();

		for(in16 x : g[node])
			if(viz[x] == false && rez[node][x] > 0) {
				ant[x] = node;
				q.push(x);
				viz[x] = true;
			}
	}

	return viz[d];
}

void solve() {

	int maxPaths = 0;

	while(bfs(s, d)) {

		for(int i = 1; i <= n ; ++i) {

			if(rez[i][d] > 0) {

				uin8 maxFlow = rez[i][d];

				for(int x = i ; x != s; x = ant[x])
					maxFlow = min(maxFlow, rez[ant[x]][x]);

				if(maxFlow <= 0) continue;

				rez[i][d] -= maxFlow;
				rez[d][i] += maxFlow;

				maxPaths += maxFlow;

				for(int x = i ; x != s; x = ant[x]) {
					rez[ant[x]][x] -= maxFlow;
					rez[x][ant[x]] += maxFlow;
				}
			}
		}
	}

	fout << maxPaths << '\n'; 
}

int main() {

	read(); solve();

	return 0;
}