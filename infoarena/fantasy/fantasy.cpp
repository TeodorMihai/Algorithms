#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3 + 4;

#define D 1
#define V 2
#define C 3
#define MID 4

int n, d, c, v;
int mid;
vector<int> g[NMAX];
int lvl[NMAX];
int tt[NMAX];
int mark[NMAX][4];
int mid1, mid2;

void read() {

	cin >> n >> d >> c >> v;

	for(int i = 1; i < n ; ++i) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}


void dfs(int node, int fath) {

	lvl[node] = lvl[fath] + 1;
	tt[node] = fath;
	
	for(int j = 0 ; j < 4; ++j)
		mark[node][j] = mark[fath][j];

	for(int x : g[node])
		if(x != fath)
			dfs(x, node);
}

int findson(int node, int val) {

	for(int x : g[node])
		if(mark[x][val - 1] == val)
			return x;
	return 0;
}

int lca(int x, int y) {

	while(lvl[x] != lvl[y])
		if(lvl[x] > lvl[y])
			x = tt[x];
		else 
			y = tt[y];

	while(x != y) {
		x = tt[x]; 
		y = tt[y];
	}

	return x;
}

void findmid(int d, int c) {

	mid1 = 0;
	mid2 = 0;
	int dc = lca(d, c);
	int upd = 1;
	int upc = 1;

	while(1) {

		if(d == c) {
			mid1 = d;
			break;
		}

		if(d == dc)
			upd = 0;

		if(c == dc)
			upc = 0;

		if(upd == 1)
			d = tt[d];
		else 
			d = findson(d, C);

		if(d == c) {
			mid1 = d;
		}

		if(upc == 1)
			c = tt[c];
		else 
			c = findson(c, D);

		if(mid1 == d) {
			mid2 = c;
			break;
		}

	}
}

void insertnode(int x, int y) {

	n++;

	for(int i = 0 ; i < g[x].size(); ++i)
		if(g[x][i] == y) {
			swap(g[x][i], g[x][ g[x].size() - 1]);
			g[x].pop_back();
			break;
		}

	g[x].push_back(n + 1);

	for(int i = 0 ; i < g[y].size(); ++i)
		if(g[y][i] == x) {
			swap(g[y][i], g[y][ g[y].size() - 1]);
			g[y].pop_back();
			break;
		}

	g[y].push_back(n + 1);
}



int cross(int oldx, int x, int oldy, int y) {
	if(oldx == y && x == y)
		return 1;
	return 0;
}

int go(int mid, int v, int c, int d) {

	int dmid = lca(v, d);
	int cmid = lca(d, c);
	int vmid = lca(mid, v);
	int upd = 1;
	int upc = 1;
	int upv = 1;

	int ans = 1;

	while(1) {

		int oldc = c;
		int oldv = v;
		int oldd = d;

		if(d == dmid)
			upd = 0;

		if(c == cmid)
			upc = 0;

		if(v == vmid)
			upv = 0;

		if(upd == 1)
			d = tt[d];
		else 
			d = findson(d, V);
		
		if(upc == 1)
			c = tt[c];
		else 
			c = findson(c, D);

		if(upv == 1)
			v = tt[v];
		else {
			v = findson(v, MID);
		}

		if(cross(oldd, d, oldv, v) == 1 || cross(oldc, c, oldv, v) == 1) {
			ans = 0;
			break;
		}

		if(v == c || v == d) {
			ans = 0;
			break;
		}
	}


	if(ans == 1)
		cout << "DA\n";
	else 
		cout << "NU\n";
}


void solve() {

	lvl[0] = 0;
	tt[1] = 1;


	
		
	mark[d][D - 1] = D;
	mark[v][V - 1] = V;
	mark[c][C - 1] = C;



	dfs(1, 0);

	mid1 = mid2 = 0;


	findmid(d, c);

	if(mid2 != 0) {
		insertnode(mid1, mid2);
		mid1 = n + 1;
		mark[mid1][MID - 1] = MID;
		dfs(1, 0);
	}

	//v d c mid1
	//v -> mid1. d -> mid1, c -> mid1
	go(mid1, v, d, c);
	

}

void clear1() {

	for(int i = 1; i <= n; ++i) {

		g[i].clear();

		for(int j = 0 ; j < 4; ++j)
			mark[i][j] = 0;
	}

}

int main() {

	freopen("fantasy.in", "r", stdin);
	freopen("fantasy.out", "w", stdout);


	int t;
	cin >> t;
	while(t--) {

		read();
		solve();
		clear1();
	}

	return 0;
}