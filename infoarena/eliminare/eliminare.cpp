#include <bits/stdc++.h>

using namespace std;

ifstream fin("eliminare.in");
ofstream fout("eliminare.out");

const int NMAX = 1000009;

int n; int m;

struct Interval {

	int maxi;
	int there;
};

Interval a[NMAX * 4]; 
int v[NMAX];

void construct(int nod, int st, int dr) {

	if(st == dr) {
		a[nod].maxi = st;
		a[nod].there = 1;
		return ;
	}

	int mid = (st + dr) / 2;
	construct(nod * 2, st, mid);
	construct(nod * 2 + 1, mid + 1, dr);

	a[nod].there = a[nod * 2].there + a[nod * 2 + 1].there;
	a[nod].maxi = a[nod * 2].maxi;

	if( v[ a[nod].maxi ] < v[ a[nod * 2 + 1].maxi ])
		a[nod].maxi = a[nod * 2 + 1].maxi;
}

int queryPos(int nod, int st, int dr, int cnt) {//al cnt-lea element

	if(st == dr)
		return st;

	int mid = (st + dr) / 2;

	if(a[nod * 2].there >=  cnt)
		return queryPos(nod * 2, st, mid, cnt);
	else 
		return queryPos(nod * 2 + 1, mid + 1, dr, cnt - a[nod * 2].there);
}

int query(int nod, int st, int dr, int left, int right) {
//element maxim din intervalul left, right

	if(left <= st && dr <= right) 
		return a[nod].maxi;

	int mid = (st + dr) / 2;

	//st, mid, dr
	int posSt = 0, posDr = 0;
	if(left <= mid)
		posSt = query(nod * 2, st, mid, left, right);

	if(mid + 1 <= right)
		posDr = query(nod * 2 + 1, mid + 1, dr, left, right);

	if(posSt == 0)
		return posDr;
	if(posDr == 0)
		return posSt;

	if(v[posSt] >= v[posDr])
		return posSt;

	return posDr;

}

void update(int nod, int st, int dr, int pos) {
	//updateaza arborele de intervalul pentru stegrgerea
	//elementului de pe pozitia pos din vectorul initial

	if(st == dr) {
		a[nod].maxi = 0;
		a[nod].there = 0;
		v[st] = -1;
		return ;
	}

	int mid = (st + dr) / 2;

	if(mid >= pos)
		update(nod * 2, st, mid, pos);
	else
		update(nod * 2 + 1, mid + 1, dr, pos);
	
	a[nod].there = a[nod * 2].there + a[nod * 2 + 1].there;
	
	a[nod].maxi = a[nod * 2].maxi;

	if(v[ a[nod].maxi ] < v[ a[nod * 2 + 1].maxi ])
		a[nod].maxi = a[nod * 2 + 1].maxi;
}

void read() {

	fin >> n >> m;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i];
}

void solve() {
	
	construct(1, 1, n);
	
	for(int i = 1; i <= m ; ++i) {

		int x; int y;
		fin >> x >> y;
		int st = queryPos(1, 1, n, x);
		int dr = queryPos(1, 1, n, y);
		int pos = query(1, 1, n, st, dr);
		update(1, 1, n, pos);
	}

	for(int i = 1; i <= n ; ++i)
		if(v[i] != -1)
			fout << v[i] << '\n';
}


int main() {
	read();
	solve();
	return 0;
}