#include <bits/stdc++.h>

using namespace std;

ifstream fin("hektor.in");
ofstream fout("hektor.out");

const int NMAX = 100009;

int n; int m; 

int start; int finish;

int cost[NMAX];

vector<int> g[NMAX];
vector<int> gt[NMAX];

double c[NMAX];

bool mark[NMAX];

void read() {

	fin >> n >> m >> start >> finish ;

	for(int i = 1; i <= n ; ++i) 
		fin >> cost[i];

	for(int i = 1; i <= m ; ++i) {
		int x; int y;

		fin >> x >> y;
		g[x].push_back(y);
		gt[y].push_back(x);
	}
}

void dfsT(int node) {

	mark[node] = 1;

	for(int x : gt[node]) 
		dfsT(x);
}

double compute(int node) {

	if(node == finish)
		return cost[node];

	double nr = 0;
	double co = 0;

	for(int x : g[node]) {
		if(mark[x] == 1) {
			
			co += (compute(x) + cost[node]);
			nr = nr + 1;
		}
	}
	return co / nr;
}



void solve() {

	dfsT(finish);

	fout << setprecision(6) << fixed << compute(start);
}

int main() {

	read();

	solve();

	return 0;

}