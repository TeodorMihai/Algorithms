#include <bits/stdc++.h>

using namespace std;

ifstream fin("java.in");
ofstream fout("java.out");

const int NMAX = 10009;

int nL; int nR; int m; 

vector<int> g[NMAX];

bool used[NMAX];

int pairL[NMAX];
int pairR[NMAX];

void read() {

	fin >> nL >> nR >> m;

	for(int i = 1; i <= m ; ++i) {
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
	}
}

bool pairUp(int node) {

	if(used[node] == true) return false;

	used[node] = true;

	for(int x : g[node])
		if(pairR[x] == 0) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	for(int x : g[node])
		if(pairUp(pairR[x]) == true) {
			pairR[x] = node;
			pairL[node] = x;
			return true;
		}

	return false;
}

int solve() {

	int cuplaj = 0;
	bool done = false;
	while(done == false) {

		done = true;
		memset(used, 0, sizeof(used));

		for(int i = 1; i <= nL; ++i)
			if(pairL[i] == 0 && pairUp(i)) 
					cuplaj++, done = false;
	}

	return cuplaj;
}

void clean() {

	memset(used, 0, sizeof(used));

	for(int i = 1; i <= max(nL, nR); ++i)
		g[i].clear(), pairR[i] = pairL[i] = 0;
}

int main() {

	int t;
	
	fin >> t;
	
	while(t--) {
		read();
		fout << solve() << '\n'; 
		clean();
	}

	return 0;
}