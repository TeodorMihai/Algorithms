#include <bits/stdc++.h>

using namespace std;

ifstream fin("ct.in");
ofstream fout("ct.out");

const int NMAX = 1e5 + 5;
const int LMAX = 16;

#define pp pair<int, int>

int n, m;

vector<int> g[NMAX];
int str[LMAX][NMAX];
int h[NMAX];
int lgg[NMAX];
int taken[NMAX], cnt;
vector< pair<int, pp> > ancestors;
int sons[NMAX][2];

//lanturi in arbore => lca, cauta ce mai simpla alegere pe care o poti face

void read() {

	fin >> n >> m;
	for(int i = 1; i < n; ++i) {
		int x, y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs(int node, int fath) {

	h[node] = h[fath] + 1;
	str[0][node] = fath;

	for(int x : g[node])
		if(x != fath)
			dfs(x, node);
}

int lca(int x, int y) {
     
    if(h[x] > h[y])
        swap(x, y);
     
    int urc = h[y] - h[x];
 
    while(urc > 0) {
 
        int lg = lgg[urc];
        y = str[lg][y];
        urc = h[y] - h[x];
    }
    if(x == y) return x;
 
    //h[x] = h[y]
    for(int i = LMAX - 1; i >= 0 ;--i) {
 
        if(str[i][x] && str[i][x] != str[i][y]) {
            x = str[i][x];
            y = str[i][y];
        }
    }

    return str[0][x];
}      
 

struct Cmp {

	bool operator()(const pair<int, pp>& x, const pair<int, pp>& y) {
		return h[x.first] > h[y.first];
	}
} cmph;

void dfs2(int node, int fath) {

	taken[node] = 1;
	for(int x : g[node])
		if(x != fath && taken[x] == 0)
			dfs2(x, node);
}

void solve() {

	dfs(1, 0);


	for(int i = 1; i < LMAX; ++i)
		for(int j = 1; j <= n; ++j)
			str[i][j] = str[i - 1][ str[i - 1][j] ];

	lgg[1] = 0;
	for(int i = 2; i <= n; ++i)
		lgg[i] = lgg[i / 2] + 1;

	while(m--) {

		int x, y;
		fin >> x >> y;
		int lc = lca(x, y);
		ancestors.push_back({lc, {x, y}});
	}

	sort(ancestors.begin(), ancestors.end(), cmph);
	for(auto x : ancestors) 
		if(taken[ x.second.first ] == 0 && taken[ x.second.second ] == 0) 	
			dfs2(x.first, str[0][x.first]), cnt++;

	fout << cnt << '\n';
}

void curata() {

	for(int i = 1; i <= n ; ++i)
		g[i].clear(), taken[i] = 0;

	cnt = 0;

	for(int i = 0 ; i < LMAX; ++i)
		for(int j = 0 ; j <= n; ++j)
			str[i][j] = 0;

	ancestors.clear();
}

int main() {

	int t;

	fin >> t;
	while(t--) {

		read(); 
		solve();
		curata();
	} 

	return 0;
}