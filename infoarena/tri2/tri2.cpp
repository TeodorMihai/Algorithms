#include <bits/stdc++.h>

using namespace std;

ifstream fin("tri2.in");
ofstream fout("tri2.out");

#define point pair<int, int>
#define x first
#define y second

const int NMAX = 1005;
const double PI = M_PI;

int n; int m;

point v[NMAX];
int a[NMAX][NMAX];
int aib[NMAX];
int ord[NMAX];
int seg[NMAX][NMAX];
int norm1[NMAX];
double u[NMAX];

void read() {

	fin >> n;

	for(int i = 1; i <= n ; ++i) {
		fin >> v[i].x >> v[i].y;
	}
}

struct cmp {

	point p;

	bool operator()(const int& p1, const int& p2) {

		//return 1ll * (v[p1].x - p.x) * (v[p2].y - p.y) - 1ll * (v[p1].y - p.y) * (v[p2].x - p.x) > 0ll;
		return u[p1] < u[p2];
		
	}

} cmpU;

struct cmpx {

	bool operator()(const int& p1, const int& p2) {
		return v[p1].x < v[p2].x;
	}
} cmpX;

int query(int pos) {

	int s = 0;

	for( ; pos > 0 ; pos -= pos & -pos)
		s += aib[pos];
	return s;
}

void ins(int pos) {

	for( ; pos <= n ; pos += pos & -pos)
		aib[pos]++;
}

long long det(point p1, point p2, point p3) {
	return 1ll * (p2.x - p1.x) * (p3.y - p1.y) - 1ll * (p2.y - p1.y) * (p3.x - p1.x);
}

void solve() {

	for(int i = 1; i <= n ; ++i)
		ord[i] = i;

	sort(ord + 1, ord + 1 + n, cmpX);

	for(int i = 1; i <= n; ++i)
		norm1[ord[i]] = i;

	for(int i = 1; i <= n ; ++i) {

		for(int j = 1; j <= n ; ++j)
			a[i][j] = j;

		swap(a[i][1], a[i][i]);
		point piv = v[a[i][1]];
		cmpU.p = piv;

		for(int j = 1; j <= n ; ++j)
			u[j] = atan2(v[j].y - piv.y, v[j].x - piv.x);

		sort(a[i] + 2, a[i] + 1 + n, cmpU);
		
		for(int j = 1; j <= n ; ++j)
			aib[j] = 0;

		for(int j = 2; j <= n ; ++j) {

			if(v[a[i][1]].x >= v[a[i][j]].x) continue;
			seg[a[i][1]][a[i][j]] = query(norm1[a[i][j]]) - query(norm1[a[i][1]] - 1);
			ins(norm1[a[i][j]]);
		}

	}

	fin >> m;
	int q[3];

	for(int i = 1; i <= m ; ++i) {

		fin >> q[0] >> q[1] >> q[2];
		sort(q, q + 3, cmpX);

		int ans = seg[q[0]][q[1]] + seg[q[1]][q[2]] - seg[q[0]][q[2]];
		
		if(det(v[q[1]], v[q[0]], v[q[2]]) < 0ll)
			ans++;
		fout << abs(ans) << '\n';
	}
}

int main() {

	read(); solve();

	return 0;
}