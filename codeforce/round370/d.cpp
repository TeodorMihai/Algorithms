#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int KMAX = 2008;
const int TMAX = 102;
const int SMAX = 2000 * 100 + 5;


int a, b, k, t;

int pos[KMAX];//pos[i] = cate posibiliatati sunt ca la un turn sa iei avantaj i
int d[2 * SMAX + 100][2];//d[i][j] = posibilitatile ca la turnul j, sa fie a > b cu i puncte

int mabs(int x) { return x > 0 ? x : -x; }

int ind(int x) {
	return x + SMAX;
}

int main() {

	cin >> a >> b >> k  >>  t;

	for(int i = 0 ; i <= 2 * k + 1 ; ++i)
		pos[i] = 2 * k + 1 - i;


	for(int i = 0 ; i <= 2 * k + 1; ++i)
		d[ind(i)][0] = pos[i], d[ind(-i)][0] = pos[i];

	for(int i = 2; i <= t; ++i) {

		for(int j = -SMAX; j <=  SMAX; ++j) {
			//x != 0
			d[ind(j)][1] += 1ll * d[ind(j - x)][0] * pos[x] % MOD;
			d[ind(j)][1] += 1ll * d[ind(j + x)][0] * pos[x] % MOD;
		}
	}

	return 0;
}