#include <bits/stdc++.h>

using namespace std;

const int DIMBUF = 1e6;
const int NMAX = 1005;
const int LGMAX = 9;

int n, m, d;
int a[NMAX][NMAX][2][2];
int c[NMAX][NMAX];
int e[NMAX * NMAX];
int ans = 0;

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

void read() {

	get(n); get(m);  get(d);

	memset(c, 0, sizeof(c));
	memset(e, 0, sizeof(e));

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m ; ++j)  
			get(c[i + j][i - j + m]);

	for(int i = 1 ; i <= n + m ; ++i)
		for(int j = 1 ; j <= n + m; ++j) {
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

	bool cur = 0;

	for(int l = 1; l < LGMAX; ++l) {

		int dim = (1 << l);
		int jdim = (1 << (l - 1));
		if(dim > d) break;

		cur = !cur;

		for(int i = 1 ; i <= n + m ; ++i) {

			if(i + dim - 1 > n + m) continue;

			for(int j = 1 ; j <= n + m; ++j) {

				if(j + dim - 1 > n + m) continue;

				int maxi1 = -1 , maxi2 = -1;

				for(int k1 = 0 ; k1 <= jdim; k1 += jdim)
					for(int k2 = 0 ; k2 <= jdim; k2 += jdim) {
						alege(a[i + k1][j + k2][!cur][0], maxi1, maxi2);
						if(l > 1)
							alege(a[i + k1][j + k2][!cur][1], maxi1, maxi2);
					}

				a[i][j][cur][0] = maxi1;
				a[i][j][cur][1] = maxi2;

			}
		}
	}
}

void solve() {

	constructRmq();
	ans = 0;
	int lgd = 0;

	for( ; (1 << lgd) <= d ; lgd++);
		lgd--;
	
	for(int i = 1 ; i <= n + m - d; ++i)
		for(int j = 1; j <= n + m - d; ++j) {

			int dd = d - (1 << lgd) + 1;
			int cur = lgd % 2;

			int maxi1 = -1, maxi2 = -1;

			for(int k1 = i ; k1 <= i + dd; k1 += dd)
				for(int k2 = j ; k2 <= j + dd; k2 += dd) {

					alege(a[k1][k2][cur][0], maxi1, maxi2);
					if(lgd > 0)
						alege(a[k1][k2][cur][1], maxi1, maxi2);
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