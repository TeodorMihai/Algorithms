#include <bits/stdc++.h>

using namespace std;

ifstream fin("zoo.in");
ofstream fout("zoo.out");

#define point pair<int, int>
#define x first
#define y second

const int NMAX = 16005;
const int MMAX = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n; int m;

point v[NMAX];
vector<int> a[NMAX * 4 + 10];

int cnt;
int x3, y3, x2, y2;

//a[node] contine punctele de la st la dr(cum apar in ordinea sortarii dupa x)
//ordonate dupa y intr-o lista
void construct(int node, int st, int dr) {

	if(st == dr) {
		a[node].push_back(v[st].y);
		return;
	}

	int mid = (st + dr) / 2;

	int left = node * 2;
	int right = node * 2 + 1;

	construct(left, st, mid);
	construct(right, mid + 1, dr);

	int i1 = 0 , i2 = 0;

	while(i1 < a[left].size() && i2 < a[right].size()) {

		if(a[left][i1] > a[right][i2]) 
			a[node].push_back(a[right][i2++]);
		else 
			a[node].push_back(a[left][i1++]);
	}

	for( ; i1 < a[left].size() ; ++i1) a[node].push_back(a[left][i1]);
	for( ; i2 < a[right].size(); ++i2) a[node].push_back(a[right][i2]);
}

//numarul de puncte din intervalul (l, r) care au coordonata y intre y1 si y2 inclusiv
void query(int node, int st, int dr, int l, int r) {

	if(l <= st && dr <= r) {

		int low = lower_bound(a[node].begin(), a[node].end(), y3) - a[node].begin();
		int up = upper_bound(a[node].begin(), a[node].end(), y2) - a[node].begin();

		cnt += up - low;
		return ;
	}

	int mid = (st + dr) / 2;
	int left = node * 2;
	int right = node * 2 + 1;
	//st, mid, dr
	if(l <= mid)
		query(left, st, mid, l, r);

	if(mid + 1 <= r)
		query(right, mid + 1, dr, l, r);

}

int lwbound(int x) {

	int pos , step;
	for(step = 1; step <= n ; step <<= 1);

	for(pos = 0; step ; step >>= 1)
		if(pos + step <= n && v[pos + step].x < x)
			pos += step;

	return pos + 1;
}

int upbound(int x) {

	int pos , step;
	for(step = 1; step <= n ; step <<= 1);

	for(pos = 0; step ; step >>= 1)
		if(pos + step <= n && v[pos + step].x <= x)
			pos += step;

	return pos;

}

void read() {

	fin >> n;

	for(int i = 1; i <= n ; ++i)
		fin >> v[i].x >> v[i].y;
}
	

void solve() {

	sort(v + 1, v + 1 + n);
	construct(1, 1, n);
	fin >> m;

	v[0].x = -INF;
	v[n + 1].x = INF;

	while(m--) {

		fin >> x3 >> y3 >> x2 >> y2;

		int left = lwbound(x3); // >= x1 primul cu prop asta
		int right = upbound(x2); // <= x2 ultimul cu prop asta

		if(right == 0 || left == n + 1) {
			fout << 0 << '\n';
			continue;
		}

		cnt = 0;
		query(1, 1, n, left, right);

		fout << cnt << '\n';
	}
}



int main() {

	read(); solve();

	return 0;
}