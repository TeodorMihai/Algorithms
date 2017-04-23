#include <bits/stdc++.h>

using namespace std;

ifstream fin("delay.in");
ofstream fout("delay.out");

const int NMAX = 16006;

int n, m;

vector<int> g[NMAX];
int str[14][NMAX];
int v[NMAX];
int s[NMAX * 2];
int pos[NMAX][2];
int a[NMAX * 8 + 10];
int h[NMAX];
int lgg[NMAX];

void read() {

	fin >> n;
	for(int i = 1; i <= n; ++i)
		fin >> v[i];

	for(int i = 1; i < n; ++i) {
		int x, y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
}

void dfs(int node, int fath) {

	h[node] = h[fath] + 1;

	str[0][node] = fath;
	s[++s[0]] = v[node];
	pos[node][0] = s[0];

	for(int x : g[node])
		if(x != fath)
			dfs(x, node);

	s[++s[0]] = -v[node];
	pos[node][1] = s[0];

}	

void construct(int node, int st, int dr) {
	if(st == dr) {
		a[node] = s[st];
		return ;
	}

	int mid = (st + dr) / 2;
	//st, mid, dr
	construct(node * 2 , st, mid);
	construct(node * 2 + 1, mid + 1, dr);
	a[node] = a[node * 2] + a[node * 2 + 1];
}

int query(int node, int st, int dr, int left, int right) {

	if(left <= st && dr <= right)
		return a[node];

	int mid = (st + dr) / 2;
	int sum = 0;
	//st mid dr
	if(left <= mid)
		sum += query(node * 2, st, mid, left, right);
	if(mid + 1 <= right)
		sum += query(node * 2 + 1, mid + 1, dr, left, right);
	return sum;
}

void update(int node, int st, int dr, int pos, int value) {

	if(st == dr) {
		a[node] = s[st]; return ;
	}

	int mid = (st + dr) / 2;
	if(pos <= mid)
		update(node * 2, st , mid, pos, value);
	else 
		update(node * 2 + 1, mid + 1, dr, pos, value);

	a[node] = a[node * 2] + a[node * 2 + 1];

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
	for(int i = 13; i >= 0 ;--i) {

		if(str[i][x] != str[i][y]) {
			x = str[i][x];
			y = str[i][y];
		}
	}

	return str[0][x];
}

void solve() {

	dfs(1, 0);

	for(int j = 1; j < 14; ++j)
		for(int i = 1; i <= n; ++i)
			str[j][i] = str[j - 1][ str[j - 1][i] ];
	fin >> m;

	//lgg[i] = x, 2^x <= i, biggest x
	lgg[1] = 0;

	for(int i = 2; i <= n; ++i)
		lgg[i] = lgg[i / 2] + 1;

	construct(1, 1, s[0]);

	while(m--) {

		int x, y, t;
		fin >> t >> x >> y;

		if(t == 1) {

			s[pos[x][0]] = y;
			s[pos[x][1]] = -y;
			v[x] = y;
			update(1, 1, s[0], pos[x][0], y);
			update(1, 1, s[0], pos[x][1], -y);
		}

		if(t == 2) {

			int lc = lca(x, y);

			int ans = query(1, 1, s[0], 1, pos[x][0]);

			int tolca = 0;

			if(pos[lc][0] == 1)
				tolca = 0;
			else 
				tolca  = query(1, 1, s[0], 1, pos[lc][0] - 1);
			
			ans += query(1, 1, s[0], 1, pos[y][0]);

			fout << ans - 2 * tolca - v[lc] << '\n';
		}

	}
}

int main() {

	read(); solve();

	return 0;
}