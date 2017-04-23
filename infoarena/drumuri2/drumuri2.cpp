#include <bits/stdc++.h>

using namespace std;

ifstream fin("drumuri2.in");
ofstream fout("drumuri2.out");

const int NMAX = 210;
const int INF = 0x3f3f3f3f;

int n; int m; int s; int d;

vector<int> g[NMAX];

int minCap[NMAX][NMAX];
int maxCap[NMAX][NMAX];
int flux[NMAX][NMAX];

bool viz[NMAX];

int ant[NMAX];
int in[NMAX];
int out[NMAX];
int mark[NMAX];

void read() {

	fin >> n >> m;

	for(int i = 1; i <= n; ++i) {

		g[i].push_back(i + n);
		g[i + n].push_back(i);
		maxCap[i][i + n] = n;
		minCap[i][i + n] = 1;
	}

	for(int i = 1; i <= m; ++i) {

		int x; int y;
		fin >> x >> y;

		out[x]++;
		in[y]++;
		g[x + n].push_back(y);
		minCap[x + n][y] = 0; //nu sunt obligat sa iau toate arcele doar nodurile
		maxCap[x + n][y] = INF;
		g[y].push_back(x + n);
	}

	s = 2 * n + 1;
	d = 2 * n + 3;

	g[s].push_back(s + 1);
	g[s + 1].push_back(s);

	g[d].push_back(d + 1);
	minCap[d][d + 1] = 0;
	maxCap[d][d + 1] = INF;
	g[d + 1].push_back(d);


	for(int i = 1; i <= n; ++i)
		if(in[i] == 0) {
			g[s + 1].push_back(i);
			minCap[s + 1][i] = 0;
			maxCap[s + 1][i] = INF;
			g[i].push_back(s + 1);
		}

	for(int i = 1; i <= n; ++i)
		if(out[i] == 0) {
			g[i + n].push_back(d);
			minCap[i + n][d] = 0;
			maxCap[i + n][d] = INF;
			g[d].push_back(i + n);
		}
	d++;
}

void reconstruct() {

	for(int i = 1; i <= 2 * n + 4; i++)
		for(int j = 1; j <= 2 * n + 4; j++)
			flux[i][j] = 0;

}

void dfs(int node) {

	viz[node] = true;
	//cum fac sa merg ami intai pe drumurile cum minCapacity?

	for(int x : g[node])
		if(viz[x] == false && maxCap[node][x] > flux[node][x]
			&& x <= n && mark[x] == 0) {
			ant[x] = node;
			dfs(x);
		}

	for(int x : g[node]) 
		if(viz[x] == false && maxCap[node][x] > flux[node][x] && 
			minCap[node][x] > flux[node][x]) {
			ant[x] = node;
			dfs(x);
		}

	for(int x : g[node])
		if(viz[x] == false && maxCap[node][x] > flux[node][x] && 
			flux[node][x] == 0) {
			ant[x] = node;
			dfs(x);
		}

	for(int x : g[node])
		if(viz[x] == false && maxCap[node][x] > flux[node][x]) {
			ant[x] = node;
			dfs(x);
		}
}


bool satisfy(int f) {

	//vreau sa vad daca cu fluxul f pot satisface conditiile de minim
	//ale fluxului
	maxCap[s][s + 1] = f;
	memset(mark, 0, sizeof(mark));

	for(bool go = true; go ;  ) {


		go = false;
		memset(viz, 0, sizeof(viz));
		ant[d] = 0;
		dfs(s);

		if(ant[d] == 0) break;

		for(int x = d; x != s ; x = ant[x]) {
			flux[ant[x]][x]++;
			flux[x][ant[x]]--;
		}

		for(int i = 1; i <= n; ++i)
			if(flux[i][i + n] >= 1)
				mark[i] = 1;

		for(int i = 1; i <= n; ++i)
			if(flux[i][i + n] <= 0)
				go = true;
	}

	for(int i = 1; i <= n; ++i)
		if(flux[i][i + n] == 0) 
			return false;
		
	
	reconstruct();

	return true;
}

int solve() {


	int pos = 0; int step;

	for(step = 1; step <= 1000; step <<= 1);

	for(pos = 0 ; step ; step >>= 1)
		if(pos + step <= 1000 && satisfy(pos + step) == false)
			pos += step;

	return pos + 1;
}


int main() {

	read();
	fout << solve() << '\n';
	return 0;
}