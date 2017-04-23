#include <bits/stdc++.h>

using namespace std;

ifstream fin("hamilton.in");
ofstream fout("hamilton.out");

const int NMAX = 19;
const int INF = 0x3f3f3f3f;

int n; int m;

int cost[NMAX][NMAX];
int d[1<<NMAX][NMAX];
int prev[1<<NMAX][NMAX];
//d[i][j] = costul minim al ciclului care foloseste nodurile i si se termina in j (inclusiv j)
vector<int> g[NMAX];

void read() {

	fin >> n >> m;

	for(int i = 0 ; i < n ; ++i)
		for(int j = 0 ; j < n; ++j)
			cost[i][j] = INF;

	for(int i = 1; i <= m; ++i) {
		int x, y, c; fin >> x >> y >> c;
		g[x].push_back(y);
		cost[x][y] = c;
	}

}


int main() {

	read(); 

	for(int i = 0 ; i < (1 << n) ; ++i)
		for(int j = 0 ; j < n ; ++j)
			d[i][j] = INF;

	d[1][0] = 0;

	for(int i = 1; i < (1 << n); ++i) {

		for(int j = 0 ; j < n; ++j) {

			if( ! ((1 << j) & i) ) continue; 

			for(int k : g[j]) {
				
				if( (1 << k) & i) continue;

				if(d[i + (1 << k)][k] > d[i][j] + cost[j][k]) 
					d[i + (1 << k)][k] = d[i][j] + cost[j][k];
			}
		}
	}

	int ans = INF;

	for(int i = 1 ; i < n; ++i)
		if(ans > d[ (1 << n) - 1][i] + cost[i][0])
			ans = d[ (1 << n) - 1][i] + cost[i][0];

	if(ans == INF)
		fout <<"Nu exista solutie\n";
	else 
		fout << ans << '\n';

	return 0;
}

