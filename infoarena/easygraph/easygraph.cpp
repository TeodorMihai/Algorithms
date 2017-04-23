#include <bits/stdc++.h>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

const int NMAX = 15009;
const int MMAX = 30009;
const int INF = 0x3f3f3f3f;

int n; int t; int m;

vector<int> g[NMAX];

int ord[NMAX];
bool viz[NMAX];
int v[NMAX];
int smax[NMAX];//s[i] = lantul maxim care se termina in i
bool inq[NMAX];

void read() {

	fin >> n >> m;

	for(int i = 1; i <= n; ++i) {
		fin >> v[i];
		smax[i] = -INF;
		g[i].clear();
	}

	for(int i = 1; i <= m; ++i) {
		
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
	}
}

void dfsSort(int node) {

	viz[node] = 1;

	for(int x : g[node]) 
		if(viz[x] == 0)
			dfsSort(x);

	ord[++ord[0]] = node;
} 


void bFord(int node) {

	queue<int> q; q.push(node);
	smax[node] = max(0, v[node]);
	inq[node] = true;

	while(q.empty() == false) {

		int x = q.front();
		viz[x] = 1;
		q.pop();
		inq[x] = false;

		for(int y : g[x]) {

			if(smax[y] < smax[x] + v[y]) {

				smax[y] = smax[x] + v[y];
				if(inq[y] == false) {
					q.push(y);	
					inq[y] = true;
				}
			}

		}
	}
}

void solve() {

	memset(viz, 0, sizeof(viz));
	ord[0] = 0;

	for(int i = 1; i <= n ; ++i)
		if(viz[i] == 0)
			dfsSort(i);
	
	memset(viz, 0, sizeof(viz));
	memset(inq, 0, sizeof(inq));

	for(int i = ord[0]; i > 0; --i) 
		if(viz[ord[i]] == 0)
			bFord(ord[i]);

	int maxi = -INF;

	for(int i = 1; i <= n; ++i)
		if(maxi < smax[i])
			maxi = smax[i];

	fout << maxi << '\n'; 
}

int main() {

	fin >> t;
	while(t--) {

		read();
		solve();
	}
	return 0;
}