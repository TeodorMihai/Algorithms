#include <bits/stdc++.h>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

const int NMAX = 15009;
const int MMAX = 30009;
const int INF = 0x7fffffff;

int n; int t; int m;

vector<int> g[NMAX];

int in[NMAX];
long long v[NMAX];
long long  smax[NMAX];//s[i] = lantul maxim care se termina in i

void read() {

	fin >> n >> m;

	for(int i = 1; i <= n; ++i) {
		fin >> v[i];
		smax[i] = -INF;
		g[i].clear();
		in[i] = 0;
	}

	for(int i = 1; i <= m; ++i) {
		
		int x; int y;
		fin >> x >> y;
		g[x].push_back(y);
		in[y]++;
	}
}

void solve() {

	queue<int> q;

	for(int i = 1; i <= n ; ++i)
		if(in[i] == 0) {
			smax[i] = v[i];
			q.push(i);
		}

	while(q.empty() == false) {

		int node = q.front();
		q.pop();

		for(int x : g[node]) {

			if( smax[x] < max(smax[node] + v[x], v[x]) )
				smax[x] = max(smax[node] + v[x], v[x]);

			in[x]--;

			if(in[x] == 0)
				q.push(x);
		}
	}
	
	long long  maxi = -INF;

	for(int i = 1; i <= n ; ++i)
		if(smax[i] > maxi)
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