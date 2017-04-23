#include <bits/stdc++.h>

using namespace std;

const int NMAX = 202;
const int MMAX = 202;
const int MOD = 98999;

int d[2][NMAX][NMAX];



int main() {

	freopen("stirling.in", "r", stdin);
	freopen("stirling.out", "w", stdout);

	int n, m, t;

	for(int i = 0; i < NMAX; ++i) {
		d[0][0][i] = 0;
		d[0][i][0] = 0;
		d[1][i][0] = 0;
		d[1][0][i] = 0;
	}

	d[0][1][1] = 1;
	d[1][1][1] = 1;

	for(int j = 1 ; j < NMAX; ++j)
		for(int k = 1 ; k < NMAX; ++k) {

			if(k == 1 && j == 1) continue;

			d[0][j][k] = d[0][j - 1][k - 1]  - ((j - 1) * d[0][j - 1][k]) % MOD;
			
			if(d[0][j][k] <= -MOD)
				d[0][j][k] += MOD;

			if(d[0][j][k] >= MOD)
				d[0][j][k] -= MOD;


			d[1][j][k] = d[1][j - 1][k - 1] + (k * d[1][j - 1][k]) % MOD;

			if(d[1][j][k] <= -MOD)
				d[1][j][k] += MOD;

			if(d[1][j][k] >= MOD)
				d[1][j][k] -= MOD;
		}

	scanf("%d", &t);

	while(t--) {

		int speta;
		scanf("%d%d%d",&speta, &n, &m);

		if(speta == 1)
			printf("%d\n", d[0][n][m]);

		if(speta == 2)
			printf("%d\n", d[1][n][m]);


	}


	return 0;
}