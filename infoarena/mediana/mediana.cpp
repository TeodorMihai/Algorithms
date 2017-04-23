#include <bits/stdc++.h>

using namespace std;

ifstream fin("mediana.in");
ofstream fout("mediana.out");

const int NMAX = 1e5 + 5;
const int DIMBUF = 1e6;

int n, m, q, t;
int a[NMAX], b[NMAX];
int ab[NMAX * 2][2];
int posa[NMAX][2];// posa[i][0]cate elemente sun strict mai mici decat a[i]
int posb[NMAX][2];
int mid;

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

void compune() {

	int i = 1, j = 1;
	int cnt = 0;

	while(i <= n && j <= m) {

		if(a[i] < b[j]) {
			cnt++;
			ab[cnt][0] = i;
			ab[cnt][1] = 0;
			i++;
		} else {
			ab[++cnt][0] = j;
			ab[cnt][1] = 1;
			j++;
		}
	}

	for( ; i <= n; ++i) 
		ab[++cnt][0] = i, ab[cnt][1] = 0;

	for( ; j <= m; ++j)
		ab[++cnt][0] = j, ab[cnt][1] = 1;
}

int lb2(int* v, int n, int x) { //cate sunt struct mai mici ca x

	int step = (1 << 16);
	int pos = 0;
	for( ; step ; step >>= 1)
		if(pos + step <= n && v[pos + step] < x)
			pos += step;
	return pos;
}


int check(int le1, int ri1, int le2, int ri2, int x) {

	int ind = ab[x][0];
	if(ab[x][1] == 0) { //din a

		int la = min(ri1 - le1 + 1, posa[ind][0] - le1 + 1);
		int lb = min(ri2 - le2 + 1, posa[ind][1] - le2 + 1);
		la = max(la, 0);
		lb = max(lb, 0);
		if(la + lb + 1 <= mid) return 1;

		return 0;

	} else {

		int la = min(ri1 - le1 + 1, posb[ind][0] - le1 + 1);
		int lb = min(ri2 - le2 + 1, posb[ind][1] - le2 + 1);
		la = max(la, 0);
		lb = max(lb, 0);

		if(la + lb + 1 <= mid) return 1;

		return 0;
	}
}

int main() {

	freopen("mediana.in", "r", stdin);
	freopen("mediana.out", "w", stdout);
	fread(buff, 1, DIMBUF, stdin);
	len = strlen(buff);
	get(t);

	while(t--) {

		get(n); get(m); get(q);

		for(int i = 1 ; i <= n ; ++i)
			get(a[i]);
		for(int i = 1 ; i <= m ; ++i)
			get(b[i]);

		for(int i = 1; i <= n; ++i) {
			
			if(a[i] != a[i - 1] || i == 1)
				posa[i][0] = i - 1;
			else 
				posa[i][0] = posa[i - 1][0];
			posa[i][1] = lb2(b, m, a[i]);
		}

		for(int i = 1; i <= m; ++i) {

			posb[i][0] = lb2(a, n, b[i]);

			if(b[i] != b[i - 1] || i == 1)
				posb[i][1] = i - 1;
			else 
				posb[i][1] = posb[i - 1][1];
		}

		compune();

		while(q--) {

			int le1, ri1, le2, ri2;
			get(le1); get(ri1); get(le2); get(ri2);
			le1++; ri1++; le2++; ri2++;

			int step = (1 << 17);
			int pos = 1;
			int cnt = ri1 + ri2 - le1 - le2 + 2;
			mid = (cnt / 2) + (cnt % 2);
						
			for( ; step ; step >>= 1)
				if(pos + step <= n + m && check(le1, ri1, le2, ri2, pos + step))
					pos += step;
			
			if(ab[pos][1] == 0)
				printf("%d\n", a[ab[pos][0]]);
			else 
				printf("%d\n", b[ab[pos][0]]);
		}
	}

	return 0;
}