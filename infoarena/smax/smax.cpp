#include <bits/stdc++.h>

using namespace std;

#define pp pair<int, int>
#define x first
#define y second

const int DIMBUF = 1e6;
const int NMAX = 1007;
const int LGMAX = 9;

int n, m, d;
int a[NMAX][NMAX / 2 + 10][LGMAX][2];
int b[NMAX][NMAX];
int c[NMAX][NMAX / 2 + 10];
int e[NMAX * (NMAX / 2 + 10)];

int lgg[NMAX];
int ans = 0;
int inf, sup;

char buff[DIMBUF]; int p; int len;
 
int get(int& x) {
 
    while(p < len && !('0' <= buff[p] && buff[p] <= '9' ) ) {
        ++p;
        if(p == DIMBUF)
            fread(buff, 1, DIMBUF, stdin), p = 0, len = strlen(buff);
    }
 
    x = 0;
    while(p < len && '0' <= buff[p] && buff[p] <= '9')  {
        x = x * 10 + buff[p] - '0';
        ++p;
        if(p == DIMBUF)
            fread(buff, 1, DIMBUF, stdin), p = 0 , len = strlen(buff);
 
    }
}

int getNr(int x, int y) { return x * NMAX + y; }
pp getPos(int nr) { return {nr / NMAX, nr % NMAX};    }

void read() {

	get(n); get(m);  get(d);

	sup = 0; inf = NMAX;

	memset(c, 0, sizeof(c));
	memset(e, 0, sizeof(e));

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m ; ++j) 
			get(b[i][j]);

	int mid = 255;
	int start = mid + 1;

	for(int i = 0 ; i < n; ++i) {

		start--;
		int x = i;
		int y = 0;
		int cnt = 0;
		for( ; x >= 0 && y < m; --x, ++y, cnt += 2) {
			c[i][start + cnt] = b[x][y];
			sup = max(start + cnt, sup);
			inf = min(start + cnt, inf);
		}
			
	}

	for(int j = 1; j < m ; ++j) {

		start++;
		int x = n - 1;
		int y = j;
		int cnt = 0;
		for( ; x >= 0 && y < m ; --x, ++y, cnt += 2) {
			c[n + j - 1][start + cnt] = b[x][y];
			sup = max(sup, start + cnt);
			inf = min(inf, start + cnt);
		}
	}

	for(int i = 0 ; i < n + m ; ++i)
		for(int j = inf ; j <= sup; ++j) {
			a[i][j][0][0] = getNr(i, j);
			e[getNr(i, j)] = c[i][j];
			a[i][j][0][1] = -1;
		}
}

void alege(int ind, int& maxi1, int& maxi2) {

	if(e[ind] > e[maxi1]) {
		maxi2 = maxi1;
		maxi1 = ind;
	} else if(e[ind] > e[maxi2] && maxi1 != ind) 
		maxi2 = ind;
}


void constructRmq() {

	for(int l = 1; l < LGMAX; ++l) {

		int dim = (1 << l);
		int jdim = (1 << (l - 1));
		if(dim > d) continue;

		for(int i = 0 ; i < n + m ; ++i) {

			if(i + dim - 1 >= n + m) continue;

			for(int j = inf ; j <= sup; ++j) {

				if(j + dim - 1 > sup) continue;

				int maxi1 = -1 , maxi2 = -1;

				for(int k1 = 0 ; k1 <= jdim; k1 += jdim)
					for(int k2 = 0 ; k2 <= jdim; k2 += jdim) {
						alege(a[i + k1][j + k2][l - 1][0], maxi1, maxi2);
						if(l > 1)
							alege(a[i + k1][j + k2][l - 1][1], maxi1, maxi2);
					}

				a[i][j][l][0] = maxi1;
				a[i][j][l][1] = maxi2;

			}
		}
	}
}

void solve() {

	constructRmq();
	lgg[1] = 0;
	ans = 0;

	for(int i = 2; i < NMAX; ++i)
		lgg[i] = lgg[i / 2] + 1;
	
	for(int i = 0 ; i < n + m - d; ++i)
		for(int j = inf ; j <= sup - d; ++j) {

			int dd = d - (1 << lgg[d]) + 1;
			int maxi1 = -1, maxi2 = -1;

			for(int k1 = i ; k1 <= i + dd; k1 += dd)
				for(int k2 = j ; k2 <= j + dd; k2 += dd) {

					alege(a[k1][k2][lgg[d]][0], maxi1, maxi2);
					if(lgg[d] > 0)
						alege(a[k1][k2][lgg[d]][1], maxi1, maxi2);
				}


			if(e[maxi1] + e[maxi2] > ans) 
				ans = e[maxi1] + e[maxi2];
		}

	printf("%d\n", ans);

}

int main() {

	int t;

	freopen("smax.in", "r", stdin);
	freopen("smax.out", "w", stdout);
	fread(buff, 1, DIMBUF, stdin);
	len = strlen(buff);
	get(t);

	while(t--) {

		read(); solve();

	}

	return 0;
}