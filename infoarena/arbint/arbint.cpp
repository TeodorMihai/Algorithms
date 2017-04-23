#include <bits/stdc++.h>

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

const int NMAX = 1e5 + 5;

int n, m;

int v[NMAX];
int a[NMAX * 4];

void construct(int node, int st, int dr) {

	if(st == dr) {
		a[node] = v[st];
		return ;
	}

	int mid = st + (dr - st) / 2;

	construct(node * 2, st, mid);
	construct(node * 2 + 1, mid + 1, dr);
	a[node] = max(a[node * 2], a[node * 2 + 1]);
}

int query(int node, int st, int dr, int left, int right) {

	if(left <= st && dr <= right) 
		return a[node];
	
	int mid = st + (dr - st) / 2;

	int rez = 0;
	//st, mid, dr
	if(left <= mid)
		rez = query(node * 2, st, mid, left, right);
	
	if(mid + 1 <= right)
		rez = max( rez, query(node * 2 + 1, mid + 1, dr, left, right));

	return rez;
}

void update(int node, int st, int dr, int pos, int value) {

	if(st == dr) {
		a[node] = value;
		return ;
	}

	int mid = st + (dr - st) / 2;
	if(pos <= mid)
		update(node * 2, st, mid, pos, value);
	else 
		update(node * 2 + 1, mid + 1, dr, pos, value);

	a[node] = max(a[node * 2], a[node * 2 + 1]);
}


int main() {

	fin >> n >> m ;
	for(int i = 1; i <= n ; ++i)
		fin >> v[i];

	construct(1, 1, n);

	for(int i = 1; i <= m ; ++i) {
		int t, x, y; fin >> t >> x >> y;
		if(t == 0) 
			fout << query(1, 1, n, x, y) << '\n';
		if(t == 1)
			update(1, 1, n, x, y);
	}
	return 0;
}