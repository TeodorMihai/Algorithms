#include <bits/stdc++.h>

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

const int NMAX = 100002;

int n;

int a[4 * NMAX];

int query(int nod,int st, int dr, int left, int right) {
	
	if(left <= st && dr <= right)
		return a[nod];

	int maxi = 0;
	int mid = (st + dr) / 2;
	//st , mid, dr
	if(left <= mid)
		maxi = query(nod * 2, st, mid, left, right);

	if(mid + 1 <= right)
		maxi = max(maxi, query(nod * 2 + 1 , mid + 1, dr, left , right));

	return maxi;
}

int update(int nod, int n, int st, int dr, int pos, int value) {

	if(st == dr) {
		a[nod] = value;
		return value;
	}

	int mid = (st + dr) / 2;
	int x = 0;
	if(pos <= mid)
		a[nod * 2] = update(nod * 2, n, st, mid, pos, value);
	else 
		a[nod * 2 + 1] = update(nod * 2 + 1, n, mid + 1, dr, pos, value);
	return (a[nod] = max(a[nod * 2], a[nod * 2 + 1]));
}

int main() {

	int type; int m;
	fin >> n >> m;

	for(int i = 1; i <= n ; ++i) {
		int x; fin >> x;
		update(1, n, 1, n, i, x);
	}

	while(m--) {

		int x; int y;
		fin >> type >> x >> y;
		if(type == 0)
			fout << query(1, 1, n, x, y) << '\n'; 
		if(type == 1)
			update(1, n, 1, n, x, y);
	}


}